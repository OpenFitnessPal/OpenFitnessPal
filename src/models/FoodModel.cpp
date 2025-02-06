#include "models/FoodModel.h"

#include <CacheManager.h>

FoodModel::FoodModel(QObject *parent)
    : QAbstractListModel{parent}
{
    m_ofp = new OFPManager(this);
    m_food = new FoodManager(this);
}

int FoodModel::rowCount(const QModelIndex &parent) const
{
    return m_data.size();
}

int FoodModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant FoodModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    FoodServing f = m_data[index.row()];
    switch (role) {
    case ITEM:
        return QVariant::fromValue(f.item);
    case NAME:
        return f.item.name();
    case SIZE:
        return QVariant::fromValue(f.size());
    case SIZEIDX:
        return f.sizeIdx;
    case UNITS:
        return f.units;
    case ID:
        return index.row();
    case MEAL:
        return m_meal;
    case SERVING:
        return QVariant::fromValue(f);
    }

    return QVariant();
}

QList<FoodServing> FoodModel::foods() const
{
    return m_data;
}

void FoodModel::add(const FoodItem &item, const ServingSize &size, const double units)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    FoodServing s;
    s.item = item;
    s.sizeIdx = item.servingSizes().indexOf(size);
    s.units = units;

    m_data << s;
    endInsertRows();

    resetCalories();
    emit dataChanged();
}

void FoodModel::add(const FoodItem &item)
{
    add(item, item.defaultServing(), 1);
}

void FoodModel::add(const FoodServing &serving)
{
    add(serving.item, serving.size(), serving.units);
}

void FoodModel::add(const QList<FoodServing> &serving)
{
    for (const FoodServing &s : serving) {
        add(s);
    }
}

void FoodModel::clear()
{
    removeRows(0, m_data.count());
}

void FoodModel::remove(int index)
{
    removeRows(index, 1, QModelIndex());
}


bool FoodModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (count == 0) return false;

    beginRemoveRows(parent, row, row + count - 1);
    m_data.remove(row, count);
    endRemoveRows();

    emit dataChanged();

    resetCalories();

    return true;
}

void FoodModel::cache(const FoodItem &item)
{
    CacheManager::cache(item);
}

void FoodModel::cache(const QList<FoodServing> &item)
{
    for (const FoodServing &s : item) {
        CacheManager::cache(s.item);
    }
}

bool FoodModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
        return false;
    }

    FoodServing &s = m_data[index.row()];

    switch (role) {
    case ITEM:
        s.item = value.value<FoodItem>();
        break;
    case NAME:
        s.item.setName(value.toString());
        break;
    case SIZE:
        s.sizeIdx = s.item.servingSizes().indexOf(value.value<ServingSize>());
        break;
    case SIZEIDX:
        s.sizeIdx = value.toInt();
        break;
    case UNITS:
        s.units = value.toDouble();
        break;
    case SERVING:
        m_data.replace(index.row(), value.value<FoodServing>());
        break;
    default:
        return false;
    }
    resetCalories();

    emit dataChanged();

    return true;
}

void FoodModel::search(const QString &query)
{
    if (m_data.size() > 0) {
        removeRows(0, m_data.size(), QModelIndex());
    }

    if (!m_offlineSearch) {
        emit m_ofp->cancelAll();

        SearchOptions options;

        options.generics = m_settings->preferGenerics();
        QVariant results = m_settings->results();
        if (results.isValid()) options.results = results.toInt();

        m_ofp->search(query, options);
        connect(m_ofp, &OFPManager::searchComplete, this, [this](const QList<FoodItem> &foods) {
            for (const FoodItem &food : foods) {
                add(food);
            }

            emit searchComplete();
        }, Qt::SingleShotConnection);
    } else {
        for (const FoodItem &item : CacheManager::search(query)) {
            add(item);
        }
    }
}

void FoodModel::load()
{
    beginResetModel();
    m_data.clear();

    auto foods = m_food->load();

    m_data.append(foods);
    resetCalories();
    endResetModel();
}

void FoodModel::save()
{
    m_food->save(m_data);
}

int FoodModel::meal() const
{
    return m_meal;
}

void FoodModel::setMeal(int newMeal)
{
    m_meal = newMeal;
    m_food->setMeal(newMeal);
    emit mealChanged();
}

bool FoodModel::offlineSearch() const
{
    return m_offlineSearch;
}

void FoodModel::setOfflineSearch(bool newOfflineSearch)
{
    if (m_offlineSearch == newOfflineSearch)
        return;
    m_offlineSearch = newOfflineSearch;
    emit offlineSearchChanged();
}

SearchSettingsManager *FoodModel::settings() const
{
    return m_settings;
}

void FoodModel::setSettings(SearchSettingsManager *newSettings)
{
    if (m_settings == newSettings)
        return;
    m_settings = newSettings;
    emit settingsChanged();
}

QDateTime FoodModel::date() const
{
    return m_date;
}

void FoodModel::setDate(const QDateTime &newDate)
{
    if (m_date == newDate)
        return;
    m_date = newDate;
    m_food->setDate(newDate.date());

    // if (m_meal == 1) qDebug() << "C++: FoodModel Date:" << newDate;
    // if (m_meal == 1) qDebug() << "C++: FoodManager Date:" << m_food->date();

    load();
    emit dateChanged();
}

double FoodModel::calories() const
{
    return m_calories;
}

void FoodModel::resetCalories()
{
    double sum = 0;
    for (const FoodServing &s : std::as_const(m_data)) {
        sum += s.nutrients().calories();
    }
    m_calories = sum;

    emit caloriesChanged();
    resetNutrients();
}

NutrientUnion FoodModel::nutrients() const
{
    return m_nutrients;
}

void FoodModel::resetNutrients()
{
    NutrientUnion sum{};
    for (const FoodServing &s : std::as_const(m_data)) {
        sum += s.nutrients();
    }

    m_nutrients = sum;
    emit nutrientsChanged();
}

QHash<int, QByteArray> FoodModel::roleNames() const
{
    QHash<int,QByteArray> rez;
    rez[ITEM] = "item";
    rez[NAME] = "name";
    rez[SIZE] = "size";
    rez[SIZEIDX] = "sizeIdx";
    rez[SERVING] = "serving";
    rez[UNITS] = "units";
    rez[MEAL] = "mealNumber";
    rez[ID] = "idx";
    return rez;
}
