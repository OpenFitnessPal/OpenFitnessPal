#include "data/RecipeManager.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QStandardPaths>

RecipeManager::RecipeManager(QObject *parent)
    : DataManager{parent}
{
    m_filename = "recipes.json";
}

bool RecipeManager::save(const QList<Recipe> &recipes)
{
    m_recipes = recipes;

    QJsonArray array;

    for (const Recipe &r : recipes) {
        array.append(r.toJson());
    }

    return write(array);
}

QList<Recipe> RecipeManager::load()
{
    QList<Recipe> recipes;

    QJsonArray array = readArray();

    for (QJsonValueConstRef ref : std::as_const(array)) {
        recipes.append(Recipe::fromJson(ref.toObject()));
    }

    m_recipes = recipes;
    return recipes;
}

QList<Recipe> RecipeManager::search(const QString &query)
{
    QRegularExpression regex(".*" + query + ".*", QRegularExpression::PatternOption::CaseInsensitiveOption);

    QList<Recipe> recipes;
    for (const Recipe &recipe : std::as_const(m_recipes)) {
        if (recipe.name().contains(regex)) {
            recipes.append(recipe);
        }
    }

    return recipes;
}
