#include "HealthMarker.h"

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
