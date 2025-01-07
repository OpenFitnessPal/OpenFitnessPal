#include "data/RecipeManager.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QStandardPaths>

RecipeManager::RecipeManager(QObject *parent)
    : QObject{parent}
{
    QDir dir = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    dir.mkpath(".");
    m_file = dir.absoluteFilePath("recipes.json");
}

bool RecipeManager::save(const QList<Recipe> &recipes)
{
    m_recipes = recipes;
    QFile file(m_file);

    QJsonArray array;

    for (const Recipe &r : recipes) {
        array.append(r.toJson());
    }

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        return false;
    }

    QByteArray toWrite = QJsonDocument(array).toJson();

    file.write(toWrite);

    file.close();

    return true;
}

QList<Recipe> RecipeManager::load()
{
    QList<Recipe> recipes;

    QFile f(m_file);

    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return recipes;
    }

    QByteArray data = f.readAll();

    f.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);

    QJsonArray array = doc.array();

    for (QJsonValueRef ref : array) {
        QJsonObject obj = ref.toObject();
        recipes.append(Recipe::fromJson(obj));
    }

    m_recipes = recipes;
    return recipes;
}

QList<Recipe> RecipeManager::search(const QString &query)
{
    QRegularExpression regex(".*" + query + ".*", QRegularExpression::PatternOption::CaseInsensitiveOption);

    QList<Recipe> recipes;
    for (const Recipe &recipe : m_recipes) {
        if (recipe.name().contains(regex)) {
            recipes.append(recipe);
        }
    }

    return recipes;
}
