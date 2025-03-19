#ifndef HEALTHMARKER_H
#define HEALTHMARKER_H

#include <QQmlEngine>
#include <QJsonObject>

class HealthMarker {
    Q_GADGET
    QML_VALUE_TYPE(healthMarker)

public:
    HealthMarker() = default;

    QString name;
    QVariant value;

    QJsonObject toJson() const;
    static HealthMarker fromJson(const QJsonObject &obj);
};

#endif // HEALTHMARKER_H
