#include "data/GoalManager.h"

#include <QDirIterator>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

GoalManager::GoalManager(QObject *parent)
    : QObject{parent}
{
    m_dir = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);

    resetDate();
}

QDate GoalManager::date() const
{
    return m_date;
}

void GoalManager::setDate(const QDate &newDate)
{
    if (m_date == newDate)
        return;
    m_date = newDate;
    emit dateChanged();
}

void GoalManager::resetDate()
{
    setDate(QDate::currentDate());
}

bool GoalManager::set(const QString &field, const int data)
{
    QDir dir(m_dir);
    mkDate(dir);

    QFile f(dir.absoluteFilePath("goals.json"));
    QJsonObject obj;

    fixDateIfNotExists(f, dir, true);

    // ReadWrite so that the file is created if it doesn't exist.
    if (!f.open(QIODevice::ReadWrite)) {
        return false;
    }

    obj = QJsonDocument::fromJson(f.readAll()).object();
    f.close();

    if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        return false;
    }

    obj.insert(field, data);

    f.write(QJsonDocument(obj).toJson());
    f.close();

    emit goalChanged(field, data);

    return true;
}


int GoalManager::get(const QString &field, const int defaultValue)
{
    QDir dir(m_dir);

    mkDate(dir);

    QFile f(dir.absoluteFilePath("goals.json"));
    QJsonObject obj;

    fixDateIfNotExists(f, dir, false);

    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return defaultValue;
    }

    obj = QJsonDocument::fromJson(f.readAll()).object();
    f.close();

    return obj.contains(field) ? obj.value(field).toInt(defaultValue) : defaultValue;
}

int GoalManager::getMacroGrams(const QString &key, const int defaultValue, const int caloriesPerGram)
{
    int macroPercent = get(key, defaultValue);
    int calories = get("calories", 3000);

    return (macroPercent / 100.0) * (calories / caloriesPerGram);
}

void GoalManager::fixDateIfNotExists(QFile &f, QDir &dir, bool modify)
{
    if (!f.exists() || (!modify && !dir.exists("goalsModified"))) {
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
            QString original = m_dir.absoluteFilePath(closestDate.toString("MM-dd-yyyy") + "/goals.json");

            // Remove the original in case it exists and is unmodified
            QFile::remove(dir.absoluteFilePath("goals.json"));
            QFile::copy(original, dir.absoluteFilePath("goals.json"));
        } else {
            if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
                return;
            }

            f.close();
        }
    } else if (modify) {
        QFile modified(dir.absoluteFilePath("goalsModified"));
        if (!modified.exists()) {
            modified.open(QIODevice::WriteOnly);
            modified.close();
        }
    }
}


bool GoalManager::mkDate(QDir &dir) const {
    QString dateString = m_date.toString("MM-dd-yyyy");

    if (!dir.mkpath(dateString)) {
        return false;
    }

    dir.cd(dateString);
    return true;
}
