#include "ExerciseRoutine.h"
#include <qjsonarray.h>
#include <qjsonobject.h>

ExerciseRoutine::ExerciseRoutine()
{
    m_exercises = {};
    m_name = "New Routine";
    m_notes = "Routine";
}

ExerciseRoutine::ExerciseRoutine(const ExerciseRoutine &other)
{
    m_exercises = other.exercises();
    m_name = other.name();
    m_notes = other.notes();
}

void ExerciseRoutine::addExercise(const Exercise &exercise)
{
    m_exercises.append(exercise);
}

void ExerciseRoutine::removeExercise(const Exercise &exercise)
{
    m_exercises.removeOne(exercise);
}

void ExerciseRoutine::setExercises(const QList<Exercise> &exercises)
{
    m_exercises = exercises;
}

QList<Exercise> ExerciseRoutine::exercises() const
{
    return m_exercises;
}

QString ExerciseRoutine::name() const
{
    return m_name;
}

void ExerciseRoutine::setName(const QString &newName)
{
    m_name = newName;
}

QString ExerciseRoutine::notes() const
{
    return m_notes;
}

void ExerciseRoutine::setNotes(const QString &newNotes)
{
    m_notes = newNotes;
}

QJsonObject ExerciseRoutine::toJson() const
{
    QJsonObject obj;

    obj.insert("name", m_name);
    obj.insert("notes", m_notes);

    QJsonArray arr;
    for (const Exercise &e : m_exercises) {
        arr.append(e.toJson());
    }

    obj.insert("exercises", arr);
    return obj;
}

ExerciseRoutine ExerciseRoutine::fromJson(const QJsonObject &obj)
{
    ExerciseRoutine e;

    e.setName(obj.value("name").toString());
    e.setNotes(obj.value("notes").toString());

    for (const QJsonValueRef ref : obj.value("exercises").toArray()) {
        e.addExercise(Exercise::fromJson(ref.toObject()));
    }

    return e;
}
