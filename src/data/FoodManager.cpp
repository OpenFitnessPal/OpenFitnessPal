#include "data/FoodManager.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QStandardPaths>

FoodManager::FoodManager(QObject *parent)
    : DataManager(parent)
{
    m_filename = "";
    m_useDate = true;
    m_subdir = "meals";
}

int FoodManager::meal() const
{
    return m_meal;
}

void FoodManager::setMeal(int newMeal)
{
    m_filename = QString::number(newMeal) + ".json";
    m_meal = newMeal;
    emit mealChanged();
}

bool FoodManager::save(const QList<FoodServing> &foods)
{
    QJsonArray array;

    for (const FoodServing &s : foods) {
        array.append(s.toJson());
    }

    return write(array);
}

QList<FoodServing> FoodManager::load()
{
    QList<FoodServing> servings{};

    QJsonArray array = readArray();

    qDebug() << "Loading" << m_date << m_meal << read();

    for (QJsonValueRef ref : array) {
        QJsonObject obj = ref.toObject();
        servings.append(FoodServing::fromJson(obj));
    }

    return servings;
}
