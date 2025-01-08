#include "Cardio.h"

#include <QJsonObject>

Cardio::Cardio(QObject *parent)
    : QObject{parent}
{}

Cardio::Cardio(const Cardio &other)
    : QObject(other.parent())
{
    setCalories(other.calories());
    setMinutes(other.minutes());
    setNotes(other.notes());
}

Cardio Cardio::operator=(const Cardio &other)
{
    setParent(other.parent());
    setCalories(other.calories());
    setMinutes(other.minutes());
    setNotes(other.notes());

    return *this;
}

int Cardio::calories() const
{
    return m_calories;
}

void Cardio::setCalories(int newCalories)
{
    if (m_calories == newCalories)
        return;
    m_calories = newCalories;
    emit caloriesChanged();
}

double Cardio::minutes() const
{
    return m_minutes;
}

void Cardio::setMinutes(double newMinutes)
{
    if (qFuzzyCompare(m_minutes, newMinutes))
        return;
    m_minutes = newMinutes;
    emit minutesChanged();
}

QString Cardio::notes() const
{
    return m_notes;
}

void Cardio::setNotes(const QString &newNotes)
{
    if (m_notes == newNotes)
        return;
    m_notes = newNotes;
    emit notesChanged();
}

QJsonObject Cardio::toJson() const
{
    QJsonObject obj;
    obj.insert("calories", m_calories);
    obj.insert("minutes", m_minutes);
    obj.insert("notes", m_notes);
    return obj;
}

Cardio Cardio::fromJson(const QJsonObject &obj)
{
    Cardio c;
    c.setCalories(obj.value("calories").toInt());
    c.setMinutes(obj.value("minutes").toDouble());
    c.setNotes(obj.value("notes").toString());
    return c;
}

bool operator==(const Cardio &a, const Cardio &b) {
    return a.calories() == b.calories() &&
           a.minutes() == b.minutes() &&
           a.notes() == b.notes();
}
