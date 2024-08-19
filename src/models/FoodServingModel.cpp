#include "models/FoodServingModel.h"
#include "OFPManager.h"

#include <CacheManager.h>
#include <DataManager.h>

FoodServingModel::FoodServingModel(QObject *parent)
    : QAbstractListModel{parent}
{
    m_manager = new OFPManager(this);
}


int FoodServingModel::rowCount(const QModelIndex &parent) const
{
    return m_data.size();
}

int FoodServingModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant FoodServingModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == FSMRoleTypes::ITEM) {
        return QVariant::fromValue(m_data[index.row()].item);
    } else if (role == FSMRoleTypes::SIZE) {
        return QVariant::fromValue(m_data[index.row()].size());
    } else if (role == FSMRoleTypes::UNITS) {
        return m_data[index.row()].units;
    } else if (role == FSMRoleTypes::ID) {
        return index.row();
    } else if (role == FSMRoleTypes::MEAL) {
        return m_meal;
    } else if (role == FSMRoleTypes::SERVING) {
        return QVariant::fromValue(m_data[index.row()]);
    }

    return QVariant();
}

QList<FoodServing> FoodServingModel::foods() const
{
    return m_data;
}

void FoodServingModel::loadData(QDate date)
{
    beginResetModel();
    m_data.clear();

    auto foods = DataManager::loadFoods(m_meal, date);

    m_data.append(foods);
    endResetModel();
}

void FoodServingModel::saveData(QDate date)
{
    DataManager::truncateSaveFoods(m_meal, date, m_data);
}

void FoodServingModel::add(const FoodItem &item, const ServingSize &size, const double units)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    FoodServing s;
    s.item = item;
    s.sizeIdx = item.servingSizes().indexOf(size);
    s.units = units;

    m_data << s;
    endInsertRows();
}

void FoodServingModel::add(const FoodServing &serving)
{
    add(serving.item, serving.size(), serving.units);
}

void FoodServingModel::add(const QList<FoodServing> &serving)
{
    for (const FoodServing &s : serving) {
        add(s);
    }
}

void FoodServingModel::clear()
{
    removeRows(0, m_data.count());
}

bool FoodServingModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (count == 0) return false;

    beginRemoveRows(parent, row, row + count - 1);
    m_data.remove(row, count);
    endRemoveRows();

    return true;
}

void FoodServingModel::cache(const FoodItem &item)
{
    CacheManager::cacheFoodItem(item);
}

void FoodServingModel::cache(const QList<FoodServing> &item)
{
    for (const FoodServing &s : item) {
        CacheManager::cacheFoodItem(s.item);
    }
}

Qt::ItemFlags FoodServingModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool FoodServingModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
        return false;
    }

    FoodServing s = m_data[index.row()];

    if (role == FSMRoleTypes::ITEM) {
        s.item = value.value<FoodItem>();
    } else if (role == FSMRoleTypes::SIZE) {
        s.sizeIdx = s.item.servingSizes().indexOf(value.value<ServingSize>());
    } else if (role == FSMRoleTypes::UNITS) {
        s.units = value.toDouble();
    } else if (role == FSMRoleTypes::SERVING) {
        m_data.replace(index.row(), value.value<FoodServing>());
    } else {
        return false;
    }

    return true;
}

void FoodServingModel::search(const QString &query)
{
    if (m_data.size() > 0) {
        removeRows(0, m_data.size(), QModelIndex());
    }

    if (!m_offlineSearch) {
        emit m_manager->cancelAll();

        SearchOptions options;

        options.generics = m_settings.get("generics").toBool();
        QVariant results = m_settings.get("results");
        if (results.isValid()) options.results = results.toInt();

        QVariantMap settings = m_settings.load();
        QMapIterator iter(settings);

        while (iter.hasNext()) {
            iter.next();

            QString key = iter.key();
            if (key.startsWith("avoid_")) {
                options.avoid.insert(iter.key(), iter.value().toDouble());
            }
        }

        m_manager->search(query, options);
        connect(m_manager, &OFPManager::searchComplete, this, [this](const QList<FoodItem> &foods) {
            for (const FoodItem &food : foods) {
                add(food, food.defaultServing(), 1);
            }

            emit searchComplete();
        }, Qt::SingleShotConnection);
    } else {
        for (const FoodItem &item : CacheManager::search(query)) {
            add(item, item.defaultServing(), 1);
        }
    }
}

QHash<int, QByteArray> FoodServingModel::roleNames() const
{
    QHash<int,QByteArray> rez;
    rez[ITEM] = "item";
    rez[SIZE] = "servingSize";
    rez[SERVING] = "serving";
    rez[UNITS] = "units";
    rez[MEAL] = "mealNumber";
    rez[ID] = "foodID";
    return rez;
}

bool FoodServingModel::offlineSearch() const
{
    return m_offlineSearch;
}

void FoodServingModel::setOfflineSearch(bool newOfflineSearch)
{
    if (m_offlineSearch == newOfflineSearch)
        return;
    m_offlineSearch = newOfflineSearch;
    emit offlineSearchChanged();
}

int FoodServingModel::meal() const
{
    return m_meal;
}

void FoodServingModel::setMeal(int newMeal)
{
    if (m_meal == newMeal)
        return;
    m_meal = newMeal;
    emit mealChanged();
}
