#include "ServingSize.h"

double ServingSize::baseMultiplier() const
{
    return m_baseMultiplier;
}

QString ServingSize::baseUnit() const
{
    return m_unit;
}

double ServingSize::defaultValue() const
{
    return m_defaultValue;
}

double ServingSize::multiplier(double units) const {
    return m_baseMultiplier * units;
}

void ServingSize::setDefaultValue(double newDefaultValue)
{
    m_defaultValue = newDefaultValue;
}

ServingSize ServingSize::fromJson(const QJsonObject &obj)
{
    ServingSize s;

    s.setBaseMultiplier(obj.value("mult").toDouble());
    s.setDefaultValue(obj.value("value").toDouble());
    s.setUnit(obj.value("unit").toString());

    return s;
}

QJsonObject ServingSize::toJson() const
{
    QJsonObject obj{};

    obj.insert("mult", m_baseMultiplier);
    obj.insert("unit", baseUnit());
    obj.insert("value", m_defaultValue);

    return obj;
}

void ServingSize::setUnit(const QString &newUnit)
{
    m_unit = newUnit;
}

QString ServingSize::unit(double units) const
{
    return QString::number(units * m_defaultValue) + " " + m_unit;
}

void ServingSize::setBaseMultiplier(double newBaseMultiplier)
{
    m_baseMultiplier = newBaseMultiplier;
}

ServingSize::ServingSize(double baseMultiplier, QString unit, double defaultValue) :
    m_baseMultiplier(baseMultiplier),
    m_unit(unit),
    m_defaultValue(defaultValue)
{}

ServingSize::ServingSize(const ServingSize &other) :
    m_baseMultiplier(other.baseMultiplier()),
    m_unit(other.baseUnit()),
    m_defaultValue(other.defaultValue())
{}

bool operator==(const ServingSize &a, const ServingSize &b) {
    return a.unit() == b.unit();
}

bool operator!=(const ServingSize &a, const ServingSize &b) {
    return a.baseMultiplier() != b.baseMultiplier()
           || a.unit() != b.unit();
}

