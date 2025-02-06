#include "data/FoodManager.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QStandardPaths>

FoodManager::FoodManager(QObject *parent)
    : QObject(parent)
{
    resetDate();
    m_dir = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
}

QDate FoodManager::date() const
{
    return m_date;
}

void FoodManager::setDate(const QDate &newDate)
{
    if (m_date == newDate)
        return;
    m_date = newDate;
    emit dateChanged();
}

void FoodManager::resetDate()
{
    setDate(QDate::currentDate());
}

int FoodManager::meal() const
{
    return m_meal;
}

void FoodManager::setMeal(int newMeal)
{
    m_meal = newMeal;
    emit mealChanged();
}

bool FoodManager::save(const QList<FoodServing> &foods)
{
    QDir dir(m_dir);
    mkDate(dir);

    dir.mkpath("meals");
    dir.cd("meals");

    QFile file(dir.absoluteFilePath(QString::number(m_meal) + ".json"));

    QJsonArray array;

    for (const FoodServing &s : foods) {
        array.append(s.toJson());
    }

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        return false;
    }

    QByteArray toWrite = QJsonDocument(array).toJson();

    file.write(toWrite);

    file.close();

    return true;
}

QList<FoodServing> FoodManager::load()
{
    QList<FoodServing> servings{};
    QDir dir(m_dir);
    mkDate(dir);

    dir.cd("meals");

    QFile f(dir.absoluteFilePath(QString::number(m_meal) + ".json"));

    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return servings;
    }

    QByteArray data = f.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);

    QJsonArray array = doc.array();

    for (QJsonValueRef ref : array) {
        QJsonObject obj = ref.toObject();
        servings.append(FoodServing::fromJson(obj));
    }

    f.close();

    return servings;
}

bool FoodManager::mkDate(QDir &dir) {
    QString dateString = m_date.toString("MM-dd-yyyy");

    if (!dir.mkpath(dateString)) {
        return false;
    }

    dir.cd(dateString);
    return true;
}
