#ifndef SERVINGSIZE_H
#define SERVINGSIZE_H

#include <QString>

#include <QJsonObject>

class ServingSize
{
    Q_GADGET

    Q_PROPERTY(double baseMultiplier READ baseMultiplier WRITE setBaseMultiplier)
    Q_PROPERTY(QString baseUnit READ baseUnit WRITE setUnit)
    Q_PROPERTY(QString unit READ unit)
    Q_PROPERTY(double defaultValue READ defaultValue WRITE setDefaultValue)

private:
    double m_baseMultiplier;

    QString m_unit;

    double m_defaultValue;
public:
    ServingSize(double baseMultiplier = 0, QString unit = "", double defaultValue = 0);
    ServingSize(const ServingSize &other);

    Q_INVOKABLE double multiplier(double units) const;

    double baseMultiplier() const;
    void setBaseMultiplier(double newBaseMultiplier);

    // QString unit() const;
    QString baseUnit() const;
    void setUnit(const QString &newUnit);

    Q_INVOKABLE QString unit(double units = 1) const;

    double defaultValue() const;
    void setDefaultValue(double newDefaultValue);

    static ServingSize fromJson(const QJsonObject &obj);
    QJsonObject toJson() const;
};

bool operator==(const ServingSize &a, const ServingSize &b);
bool operator!=(const ServingSize &a, const ServingSize &b);

Q_DECLARE_METATYPE(ServingSize);
Q_DECLARE_METATYPE(QList<ServingSize>);

#endif // SERVINGSIZE_H
