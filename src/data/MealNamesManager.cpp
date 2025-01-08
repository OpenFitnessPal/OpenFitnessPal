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

    resetDate();
}

bool MealNamesManager::save()
{
    QDir dir(m_dir);
    mkDate(dir);

    QFile f(dir.absoluteFilePath("mealNames.json"));
    QJsonArray arr = QJsonArray::fromStringList(m_mealNames);

    fixDateIfNotExists(f, dir, true);

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
    mkDate(dir);

    QFile f(dir.absoluteFilePath("mealNames.json"));

    fixDateIfNotExists(f, dir, false);

    if (!f.open(QIODevice::ReadOnly)) {
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

void MealNamesManager::fixDateIfNotExists(QFile &f, QDir &dir, bool modify)
{
    if (!f.exists() || (!modify && !dir.exists("mealNamesModified"))) {
        QDir rootDir(m_dir);

        QDate closestDate = QDate(1, 1, 1);

        QDirIterator iter(rootDir);
        while (iter.hasNext()) {
            iter.next();
            QString dirName = iter.fileName();
            QDate date = QDate::fromString(dirName, "MM-dd-yyyy");

            if (date.isNull() || date == m_date) continue;

            int distance = date.daysTo(m_date);

            if (distance < closestDate.daysTo(m_date)) {
                closestDate = date;
            }
        }

        if (closestDate != QDate(1, 1, 1)) {
            QString original = m_dir.absoluteFilePath(closestDate.toString("MM-dd-yyyy") + "/mealNames.json");

            // Remove the original in case it exists and is unmodified
            QFile::remove(dir.absoluteFilePath("mealNames.json"));
            QFile::copy(original, dir.absoluteFilePath("mealNames.json"));
        } else {
            if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
                return;
            }

            m_mealNames.clear();
            m_mealNames.append("Breakfast");
            m_mealNames.append("Lunch");
            m_mealNames.append("Dinner");
            m_mealNames.append("Preworkout");
            m_mealNames.append("Postworkout");

            f.write(QJsonDocument(QJsonArray::fromStringList(m_mealNames)).toJson());
            f.close();
        }
    } else if (modify) {
        QFile modified(dir.absoluteFilePath("mealNamesModified"));
        if (!modified.exists()) {
            modified.open(QIODevice::WriteOnly);
            modified.close();
        }
    }
}
