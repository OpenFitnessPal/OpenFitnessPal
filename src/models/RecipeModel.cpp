#include "models/RecipeModel.h"

#include <CacheManager.h>

RecipeModel::RecipeModel(RecipeManager *manager, QObject *parent)
    : QAbstractListModel{parent}
{
    m_manager = manager;
}


int RecipeModel::rowCount(const QModelIndex &parent) const
{
    return m_data.size();
}

int RecipeModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant RecipeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == RLMRoleTypes::FOODS) {
        return QVariant::fromValue(m_data[index.row()].foods());
    } else if (role == RLMRoleTypes::NAME) {
        return QVariant::fromValue(m_data[index.row()].name());
    } else if (role == RLMRoleTypes::UNITS) {
        return m_data[index.row()].servings();
    } else if (role == RLMRoleTypes::ID) {
        return index.row();
    } else if (role == RLMRoleTypes::RECIPE) {
        return QVariant::fromValue(m_data[index.row()]);
    } else if (role == RLMRoleTypes::NUTRIENTS) {
        return QVariant::fromValue(m_data[index.row()].nutrients());
    }

    return QVariant();
}

void RecipeModel::load()
{
    beginResetModel();
    m_data.clear();

    auto recipes = m_manager->load();

    m_data.append(recipes);
    endResetModel();
}

void RecipeModel::add(const QList<FoodServing> &foods, const QString &name, const double servings, bool doSave)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    Recipe r;
    r.setName(name);
    r.setServings(servings);
    r.setFoods(foods);

    for (const FoodServing &s : foods) {
        CacheManager::cache(s.item);
    }

    m_data << r;

    endInsertRows();

    if (doSave) {
        m_manager->save(m_data);
    }
}

void RecipeModel::clear()
{
    removeRows(0, m_data.count());
}

void RecipeModel::remove(int idx)
{
    removeRow(idx);
}

void RecipeModel::add(const Recipe &recipe)
{
    add(recipe.foods(), recipe.name(), recipe.servings());
}

void RecipeModel::add(const QList<Recipe> &recipes)
{
    for (const Recipe &recipe : recipes) {
        add(recipe);
    }
}

void RecipeModel::add(const QString &name)
{
    add(QList<FoodServing>(), name, 1);
}

void RecipeModel::search(const QString &query)
{
    clear();

    add(m_manager->search(query));
}

bool RecipeModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (count == 0) return false;

    beginRemoveRows(parent, row, row + count - 1);
    m_data.remove(row, count);
    endRemoveRows();

    m_manager->save(m_data);

    return true;
}

Qt::ItemFlags RecipeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool RecipeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
        return false;
    }

    switch (role) {
    case RLMRoleTypes::FOODS:
        m_data[index.row()].setFoods(value.value<QList<FoodServing>>());
        emit dataChanged(index, index, {role, RLMRoleTypes::NUTRIENTS});
        break;
    case RLMRoleTypes::NAME:
        m_data[index.row()].setName(value.toString());
        emit dataChanged(index, index, {role});
        break;
    case RLMRoleTypes::UNITS:
        m_data[index.row()].setServings(value.toDouble());
        emit dataChanged(index, index, {role});
        break;
    case RLMRoleTypes::RECIPE:
        m_data[index.row()] = value.value<Recipe>();
        break;
    default:
        return false;
    }

    m_manager->save(m_data);

    return true;
}

QHash<int, QByteArray> RecipeModel::roleNames() const
{
    QHash<int,QByteArray> rez;
    rez[NAME] = "name";
    rez[FOODS] = "foods";
    rez[UNITS] = "servings";
    rez[NUTRIENTS] = "nutrients";
    rez[ID] = "idx";
    rez[RECIPE] = "recipe";
    return rez;
}

int RecipeModel::meal() const
{
    return m_meal;
}

void RecipeModel::setMeal(int newMeal)
{
    if (m_meal == newMeal)
        return;
    m_meal = newMeal;
    emit mealChanged();
}
