#include "data/MealNamesManager.h"

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
    QDir m_dir = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);

    resetDate();
}

/*
 * TODO: Finish up
 * For this and all other day-based stuff (this, weight, goals, NOT exercise or food), need to figure out a way to always properly get the last-set data.
 * To do that:
 * - Disable future date setting in the GUI
 * - In the read functions, if the json doesn't exist, search for the nearest date.
 *   Copy the nearest date's json over to the new date and continue.
 * - If there's no nearest date at all, set everything to the default.
 */
bool MealNamesManager::save()
{
    QDir dir(m_dir);
    mkDate(dir);

    QFile f(dir.absoluteFilePath("meals.json"));
    QJsonObject obj;

    if (!f.open(QIODevice::ReadOnly)) {
        return false;
    }

    obj = QJsonDocument::fromJson(f.readAll()).object();
    f.close();

    if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        return false;
    }

    // obj.insert(field, data.toJsonValue());

    f.write(QJsonDocument(obj).toJson());
    f.close();

    return true;
}

QStringList MealNamesManager::load() const
{

}

QDate MealNamesManager::date() const
{
    return m_date;
}

void MealNamesManager::setDate(const QDate &newDate)
{
    if (m_date == newDate)
        return;
    m_date = newDate;
    emit dateChanged();
}

void MealNamesManager::resetDate()
{
    setDate(QDate::currentDate());
}

bool MealNamesManager::mkDate(QDir &dir) const {
    QString dateString = m_date.toString("MM-dd-yyyy");

    if (!dir.mkpath(dateString)) {
        return false;
    }

    dir.cd(dateString);
    return true;
}
