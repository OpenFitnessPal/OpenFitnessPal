#include "data/RoutineManager.h"

#include <QDir>
#include <QJsonArray>
#include <QStandardPaths>
#include <QJsonObject>
#include <QJsonDocument>

RoutineManager::RoutineManager(QObject *parent)
    : DataManager{parent}
{
    m_filename = "routines.json";
}

bool RoutineManager::save(const QList<ExerciseRoutine> &routines)
{
    m_routines = routines;

    QJsonArray array;

    for (const ExerciseRoutine &r : routines) {
        array.append(r.toJson());
    }

    return write(array);
}

QList<ExerciseRoutine> RoutineManager::load()
{
    QList<ExerciseRoutine> routines;

    QJsonArray array = readArray();

    for (QJsonValueConstRef ref : std::as_const(array)) {
        routines.append(ExerciseRoutine::fromJson(ref.toObject()));
    }

    m_routines = routines;
    return routines;
}

QList<ExerciseRoutine> RoutineManager::search(const QString &query)
{
    QRegularExpression regex(".*" + query + ".*", QRegularExpression::PatternOption::CaseInsensitiveOption);

    QList<ExerciseRoutine> routines;
    for (const ExerciseRoutine &routine : std::as_const(m_routines)) {
        if (routine.name().contains(regex)) {
            routines.append(routine);
        }
    }

    return routines;
}

