#include "data/MealNamesManager.h"

#include <QDirIterator>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

QStringList MealNamesManager::mealNames() const
{
    return m_mealNames;
}

void MealNamesManager::setMealNames(const QStringList &newMealNames)
{
    if (m_mealNames == newMealNames)
        return;
    m_mealNames = newMealNames;
    emit mealNamesChanged();
}

MealNamesManager::MealNamesManager(QObject *parent)
    : QObject(parent)
{
    m_dir = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
}

bool MealNamesManager::save()
{
    QDir dir(m_dir);

    QFile f(dir.absoluteFilePath("mealNames.json"));
    QJsonArray arr = QJsonArray::fromStringList(m_mealNames);

    if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        return false;
    }

    f.write(QJsonDocument(arr).toJson());
    f.close();

    return true;
}

QStringList MealNamesManager::load()
{
    QDir dir(m_dir);

    QFile f(dir.absoluteFilePath("mealNames.json"));

    if (!f.open(QIODevice::ReadOnly)) {
        m_mealNames.clear();
        m_mealNames.append("Breakfast");
        m_mealNames.append("Lunch");
        m_mealNames.append("Dinner");
        m_mealNames.append("Preworkout");
        m_mealNames.append("Postworkout");

        if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
            return m_mealNames;
        }

        f.write(QJsonDocument(QJsonArray::fromStringList(m_mealNames)).toJson());
        f.close();

        return m_mealNames;
    }

    m_mealNames.clear();

    QJsonDocument doc = QJsonDocument::fromJson(f.readAll());
    QJsonArray arr = doc.array();
    for (QJsonValueConstRef ref : arr) {
        m_mealNames.emplaceBack(ref.toString(""));
    }

    f.close();

    return m_mealNames;

}
