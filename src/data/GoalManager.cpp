#include "data/GoalManager.h"

#include <QDirIterator>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

int GoalManager::calories()
{
    if (m_calories == -1) m_calories = get("calories", 2000);

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
    if (m_carbs != newCarbs) {
    set("carbs", newCarbs);
    m_carbs = newCarbs;
    }

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
    if (m_fat != newFat) {
    set("fat", newFat);
    m_fat = newFat;
    }

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
    if (m_protein != newProtein) {
        set("protein", newProtein);
        m_protein = newProtein;
    }

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
    m_object = readObject();

    QMapIterator iter(m_fields);

    while (iter.hasNext()) {
        iter.next();

        emit goalChanged(iter.key(), get(iter.key(), iter.value()));
    }

    // Force-reset
    m_carbs = -1;
    m_fat = -1;
    m_protein = -1;

    setCarbs(carbs());
    setFat(fat());
    setProtein(protein());
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
    m_object.insert(field, data);

    bool ok = write(m_object);

    emit goalChanged(field, data);

    return ok;
}

int GoalManager::get(const QString &field, const int defaultValue)
{
    if (m_object.empty()) {
        m_object = readObject();
    }

    if (!m_fields.contains(field)) m_fields.insert(field, defaultValue);

    return m_object.contains(field) ? m_object.value(field).toInt(defaultValue) : defaultValue;
}

int GoalManager::getMacroGrams(const int value, const int caloriesPerGram)
{
    return (value / 100.0) * (calories() / caloriesPerGram);
}
