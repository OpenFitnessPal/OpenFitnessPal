#include "models/RecipeListModel.h"

#include <CacheManager.h>
#include <DataManager.h>

RecipeListModel::RecipeListModel(QObject *parent)
    : QAbstractListModel{parent}
{
}


int RecipeListModel::rowCount(const QModelIndex &parent) const
{
    return m_data.size();
}

int RecipeListModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant RecipeListModel::data(const QModelIndex &index, int role) const
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
    }

    return QVariant();
}

void RecipeListModel::loadData()
{
    beginResetModel();
    m_data.clear();

    auto recipes = DataManager::loadRecipes();

    m_data.append(recipes);
    endResetModel();
}

void RecipeListModel::saveData()
{
    DataManager::truncateSaveRecipes(m_data);
}

void RecipeListModel::add(const QList<FoodServing> &foods, const QString &name, const double servings)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    Recipe r;
    r.setName(name);
    r.setServings(servings);
    r.setFoods(foods);

    m_data << r;
    endInsertRows();
}

void RecipeListModel::clear()
{
    removeRows(0, m_data.count());
}

void RecipeListModel::add(const Recipe &recipe)
{
    add(recipe.foods(), recipe.name(), recipe.servings());
}

void RecipeListModel::add(const QList<Recipe> &recipes)
{
    for (const Recipe &recipe : recipes) {
        add(recipe);
    }
}

void RecipeListModel::search(const QString &query)
{
    clear();

    add(DataManager::searchRecipes(query));
}

bool RecipeListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (count == 0) return false;

    beginRemoveRows(parent, row, row + count - 1);
    m_data.remove(row, count);
    endRemoveRows();

    return true;
}

void RecipeListModel::cache(const FoodItem &item)
{
    CacheManager::cacheFoodItem(item);
}

Qt::ItemFlags RecipeListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool RecipeListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
        return false;
    }

    if (role == RLMRoleTypes::FOODS) {
        m_data[index.row()].setFoods(value.value<QList<FoodServing>>());
    } else if (role == RLMRoleTypes::NAME) {
        m_data[index.row()].setName(value.toString());
    } else if (role == RLMRoleTypes::UNITS) {
        m_data[index.row()].setServings(value.toDouble());
    } else if (role == RLMRoleTypes::RECIPE) {
        m_data[index.row()] = value.value<Recipe>();
    } else {
        return false;
    }

    return true;
}

QHash<int, QByteArray> RecipeListModel::roleNames() const
{
    QHash<int,QByteArray> rez;
    rez[NAME] = "name";
    rez[FOODS] = "foods";
    rez[UNITS] = "servings";
    rez[ID] = "recipeID";
    rez[RECIPE] = "recipe";
    return rez;
}

int RecipeListModel::meal() const
{
    return m_meal;
}

void RecipeListModel::setMeal(int newMeal)
{
    if (m_meal == newMeal)
        return;
    m_meal = newMeal;
    emit mealChanged();
}
