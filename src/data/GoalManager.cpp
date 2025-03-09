#include "data/GoalManager.h"

#include <QDirIterator>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

int GoalManager::calories()
{
    if (m_calories == -1) m_calories = get("calories", 3000);

    return m_calories;
}

void GoalManager::setCalories(int newCalories)
{
    set("calories", newCalories);
    m_calories = newCalories;

    emit caloriesChanged();
    emit carbsGramsChanged();
    emit fatGramsChanged();
    emit proteinGramsChanged();
}

int GoalManager::carbs()
{
    if (m_carbs == -1) m_carbs = get("carbs", 35);
    return m_carbs;
}

void GoalManager::setCarbs(int newCarbs)
{
    set("carbs", newCarbs);
    m_carbs = newCarbs;

    emit carbsChanged();
    emit carbsGramsChanged();
}

int GoalManager::fat()
{
    if (m_fat == -1) m_fat = get("fat", 35);

    return m_fat;
}

void GoalManager::setFat(int newFat)
{
    set("fat", newFat);
    m_fat = newFat;

    emit fatChanged();
    emit fatGramsChanged();
}

int GoalManager::protein()
{
    if (m_protein == -1) m_protein = get("protein", 30);

    return m_protein;
}

void GoalManager::setProtein(int newProtein)
{
    set("protein", newProtein);
    m_protein = newProtein;

    emit proteinChanged();
    emit proteinGramsChanged();
}

int GoalManager::carbsGrams()
{
    return getMacroGrams(carbs());
}

int GoalManager::fatGrams()
{
    return getMacroGrams(fat(), 9);
}

int GoalManager::proteinGrams()
{
    return getMacroGrams(protein());
}

void GoalManager::updateFields()
{
    QMapIterator iter(m_fields);

    while (iter.hasNext()) {
        iter.next();

        emit goalChanged(iter.key(), get(iter.key(), iter.value()));
    }

    emit carbsGramsChanged();
    emit fatGramsChanged();
    emit proteinGramsChanged();
}

GoalManager::GoalManager(QObject *parent)
    : DataManager{parent}
{
    m_filename = "goals.json";
    m_useDate = true;
    m_nearest = true;
    m_modifiedFileName = "goalsModified";
}

bool GoalManager::set(const QString &field, const int data)
{
    QJsonObject obj = readObject();
    obj.insert(field, data);

    bool ok = write(obj);

    emit goalChanged(field, data);

    return ok;
}


int GoalManager::get(const QString &field, const int defaultValue)
{
    if (!m_fields.contains(field)) m_fields.insert(field, defaultValue);

    QJsonObject obj = readObject();

    return obj.contains(field) ? obj.value(field).toInt(defaultValue) : defaultValue;
}

int GoalManager::getMacroGrams(const int value, const int caloriesPerGram)
{
    return (value / 100.0) * (calories() / caloriesPerGram);
}
