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
    setName(other.name());
}

Cardio Cardio::operator=(const Cardio &other)
{
    setParent(other.parent());
    setCalories(other.calories());
    setMinutes(other.minutes());
    setName(other.name());

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

QString Cardio::name() const
{
    return m_name;
}

void Cardio::setName(const QString &newname)
{
    if (m_name == newname)
        return;
    m_name = newname;
    emit nameChanged();
}

QJsonObject Cardio::toJson() const
{
    QJsonObject obj;
    obj.insert("calories", m_calories);
    obj.insert("minutes", m_minutes);
    obj.insert("name", m_name);
    return obj;
}

Cardio Cardio::fromJson(const QJsonObject &obj)
{
    Cardio c;
    c.setCalories(obj.value("calories").toInt());
    c.setMinutes(obj.value("minutes").toDouble());
    c.setName(obj.value("name").toString());
    return c;
}

bool operator==(const Cardio &a, const Cardio &b) {
    return a.calories() == b.calories() &&
           a.minutes() == b.minutes() &&
           a.name() == b.name();
}
