#include "Exercise.h"

#include <qjsonarray.h>
#include <qjsonobject.h>

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

QJsonObject Exercise::toJson() const
{
    QJsonObject obj;
    obj.insert("name", m_name);
    QJsonArray arr;
    for (const ExerciseSet &s : m_sets) {
        arr.append(s.toJson());
    }
    obj.insert("sets", arr);
    return obj;
}

Exercise Exercise::fromJson(const QJsonObject &obj)
{
    Exercise e;
    e.setName(obj.value("name").toString());

    QList<ExerciseSet> sets;
    for (const QJsonValueRef ref : obj.value("sets").toArray()) {
        sets.append(ExerciseSet::fromJson(ref.toObject()));
    }
    e.setSets(sets);
    return e;
}

bool Exercise::operator==(const Exercise &other) const
{
    return m_name == other.name() && m_sets == other.sets();
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

