#include "data/RoutineManager.h"

#include <QDir>
#include <QJsonArray>
#include <QStandardPaths>
#include <QJsonObject>
#include <QJsonDocument>

RoutineManager::RoutineManager(QObject *parent)
    : QObject{parent}
{
    QDir dir = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    dir.mkpath(".");
    m_file = dir.absoluteFilePath("routines.json");
}

bool RoutineManager::save(const QList<ExerciseRoutine> &routines)
{
    m_routines = routines;
    QFile file(m_file);

    QJsonArray array;

    for (const ExerciseRoutine &r : routines) {
        array.append(r.toJson());
    }

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        return false;
    }

    QByteArray toWrite = QJsonDocument(array).toJson();

    file.write(toWrite);

    file.close();

    return true;
}

QList<ExerciseRoutine> RoutineManager::load()
{
    QList<ExerciseRoutine> routines;

    QFile f(m_file);

    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return routines;
    }

    QByteArray data = f.readAll();
    f.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);

    QJsonArray array = doc.array();

    for (QJsonValueRef ref : array) {
        QJsonObject obj = ref.toObject();
        routines.append(ExerciseRoutine::fromJson(obj));
    }

    m_routines = routines;
    return routines;
}

QList<ExerciseRoutine> RoutineManager::search(const QString &query)
{
    QRegularExpression regex(".*" + query + ".*", QRegularExpression::PatternOption::CaseInsensitiveOption);

    QList<ExerciseRoutine> routines;
    for (const ExerciseRoutine &routine : m_routines) {
        if (routine.name().contains(regex)) {
            routines.append(routine);
        }
    }

    return routines;
}

