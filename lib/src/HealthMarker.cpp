#include "HealthMarker.h"

QString HealthMarker::getName() const
{
    return name;
}

void HealthMarker::setName(const QString &newName)
{
    if (name == newName)
        return;
    name = newName;
}

QVariant HealthMarker::getValue() const
{
    return value;
}

void HealthMarker::setValue(const QVariant &newValue)
{
    if (value == newValue)
        return;
    value = newValue;
}

QJsonObject HealthMarker::toJson() const
{
    QJsonObject obj;

    obj.insert("name", name);
    obj.insert("value", value.toJsonValue());

    return obj;
}

HealthMarker HealthMarker::fromJson(const QJsonObject &obj)
{
    HealthMarker marker;
    marker.name = obj.value("name").toString();
    marker.value = obj.value("value");

    return marker;
}
