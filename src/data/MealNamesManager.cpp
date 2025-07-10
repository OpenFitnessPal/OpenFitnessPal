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
    : DataManager(parent)
{
    m_filename = "mealNames.json";
}

bool MealNamesManager::save()
{
    QJsonArray arr = QJsonArray::fromStringList(m_mealNames);

    return write(arr);
}

QStringList MealNamesManager::load()
{
    QByteArray data = read();

    if (data.isEmpty()) {
        m_mealNames.clear();
        m_mealNames.append("Breakfast");
        m_mealNames.append("Lunch");
        m_mealNames.append("Dinner");
        m_mealNames.append("Preworkout");
        m_mealNames.append("Postworkout");

        save();

        return m_mealNames;
    }

    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray arr = doc.array();

    for (QJsonValueConstRef ref : arr) {
        m_mealNames.emplaceBack(ref.toString(""));
    }

    return m_mealNames;

}
