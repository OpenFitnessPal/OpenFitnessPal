#include "data/ExerciseManager.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

ExerciseManager::ExerciseManager(QObject *parent)
    : DataManager{parent}
{
    m_filename = "exercises.json";
    m_useDate = true;
}

QList<Exercise> ExerciseManager::load()
{
    QList<Exercise> exercises{};

    QJsonArray arr = readArray();

    for (const QJsonValueRef ref : arr) {
        exercises.append(Exercise::fromJson(ref.toObject()));
    }

    return exercises;
}

bool ExerciseManager::save(const QList<Exercise> &exercises)
{
    QJsonArray arr;

    for (const Exercise & ex : exercises) {
        arr.append(ex.toJson());
    }

    return write(arr);
}
