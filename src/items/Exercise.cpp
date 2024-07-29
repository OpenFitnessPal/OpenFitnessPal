#include "items/Exercise.h"
#include "data/DataManager.h"

Exercise::Exercise(QObject *parent)
    : QObject(parent)
{
}

Exercise::Exercise(const Exercise &other)
    : QObject(other.parent())
{
    m_name = other.name();
    m_sets = other.sets();
}

Exercise Exercise::operator=(const Exercise &other)
{
    setParent(other.parent());
    m_name = other.name();
    m_sets = other.sets();

    return *this;
}

QString Exercise::name() const
{
    return m_name;
}

void Exercise::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
}

QList<ExerciseSet> Exercise::sets() const
{
    return (m_sets);
}

void Exercise::setSets(const QList<ExerciseSet> &newSets)
{
    m_sets = newSets;
}


void Exercise::addSet()
{
    ExerciseSet set;
    m_sets.append(set);
}

void Exercise::addSet(int reps, int weight)
{
    ExerciseSet set;
    set.setReps(reps);
    set.setWeight(weight);
    m_sets.append(set);
}

void Exercise::removeSet(int idx)
{
    m_sets.removeAt(idx);
}

void Exercise::changeSet(int idx, int reps, int weight)
{
    ExerciseSet set = m_sets.at(idx);
    set.setReps(reps);
    set.setWeight(weight);
    m_sets.replace(idx, set);
}

