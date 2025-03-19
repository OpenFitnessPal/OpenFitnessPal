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

    QString getName() const;
    void setName(const QString &newName);

    QVariant getValue() const;
    void setValue(const QVariant &newValue);

private:
    Q_PROPERTY(QString name READ getName WRITE setName FINAL)
    Q_PROPERTY(QVariant value READ getValue WRITE setValue FINAL)
};

#endif // HEALTHMARKER_H
