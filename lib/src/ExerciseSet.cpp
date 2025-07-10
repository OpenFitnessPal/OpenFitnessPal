#include "ExerciseSet.h"

#include <QTime>
#include <QJSValue>
#include <qjsonobject.h>

ExerciseSet::ExerciseSet(QObject *parent)
    : QObject(parent)
{
}

ExerciseSet::ExerciseSet(const ExerciseSet &other)
    : QObject(other.parent())
{
    setReps(other.reps());
    setWeight(other.weight());
}

ExerciseSet ExerciseSet::operator=(const ExerciseSet &other)
{
    setParent(other.parent());
    setReps(other.reps());
    setWeight(other.weight());

    return *this;
}

int ExerciseSet::weight() const
{
    return m_weight;
}

void ExerciseSet::setWeight(int newWeight)
{
    if (m_weight == newWeight)
        return;

    m_weight = newWeight;
    emit weightChanged();
}

QJsonObject ExerciseSet::toJson() const
{
    QJsonObject obj;
    obj.insert("reps", m_reps);
    obj.insert("weight", m_weight);
    return obj;
}

ExerciseSet ExerciseSet::fromJson(const QJsonObject &obj)
{
    ExerciseSet e;
    e.setReps(obj.value("reps").toInt());
    e.setWeight(obj.value("weight").toInt());
    return e;
}

int ExerciseSet::reps() const
{
    return m_reps;
}

void ExerciseSet::setReps(int newReps)
{
    if (m_reps == newReps)
        return;
    m_reps = newReps;
    emit repsChanged();
}

bool operator==(const ExerciseSet &a, const ExerciseSet &b) {
    return a.reps() == b.reps() && a.weight() == b.weight();
}
