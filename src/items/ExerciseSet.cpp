#include "items/ExerciseSet.h"

#include <QTime>
#include <QJSValue>

ExerciseSet::ExerciseSet(QObject *parent)
    : QObject(parent)
{
}

ExerciseSet::ExerciseSet(const ExerciseSet &other)
    : QObject(other.parent())
{
    setReps(other.reps());
    setWeight(other.weight());
    // setTime(other->time());
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
    // emit weightChanged();
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
    // emit repsChanged();
}
