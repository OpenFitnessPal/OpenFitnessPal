#include "data/ExerciseManager.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

ExerciseManager::ExerciseManager(QObject *parent)
    : QObject{parent}
{
    resetDate();
    m_dir = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
}

QDate ExerciseManager::date() const
{
    return m_date;
}

void ExerciseManager::setDate(const QDate &newDate)
{
    if (m_date == newDate)
        return;
    m_date = newDate;
    emit dateChanged();
}

void ExerciseManager::resetDate()
{
    setDate(QDate::currentDate());
}

QList<Exercise> ExerciseManager::load()
{
    QList<Exercise> exercises{};
    QDir dir(m_dir);

    mkDate(dir);

    QFile file(dir.absoluteFilePath("exercises.json"));

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return exercises;
    }

    QByteArray data = file.readAll();

    file.close();

    QJsonArray arr = QJsonDocument::fromJson(data).array();

    for (const QJsonValueRef ref : arr) {
        exercises.append(Exercise::fromJson(ref.toObject()));
    }

    return exercises;
}

bool ExerciseManager::save(const QList<Exercise> &exercises)
{
    QDir dir(m_dir);

    mkDate(dir);

    QFile file(dir.absoluteFilePath("exercises.json"));

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        return false;
    }

    QJsonArray arr;

    for (const Exercise & ex : exercises) {
        arr.append(ex.toJson());
    }

    file.write(QJsonDocument(arr).toJson());

    return true;
}

bool ExerciseManager::mkDate(QDir &dir) {
    QString dateString = m_date.toString("MM-dd-yyyy");

    if (!dir.mkpath(dateString)) {
        return false;
    }

    dir.cd(dateString);
    return true;
}
