#ifndef HealthMarkerManager_H
#define HealthMarkerManager_H

#include "DataManager.h"

#include <QDir>
#include <QObject>
#include <QQmlEngine>

typedef struct HealthMarker {
    QString name;
    QVariant value;

    QJsonObject toJson() const;
    static HealthMarker fromJson(const QJsonObject &obj);
} HealthMarker;

class HealthMarkerManager : public DataManager
{
    Q_OBJECT
    QML_ELEMENT

    QList<HealthMarker> m_markers;
public:
    HealthMarkerManager(QObject *parent = nullptr);

    bool save(const QList<HealthMarker> &markers);
    QList<HealthMarker> load();

signals:
    void dataChanged(const QString &name, const QVariant &data);
};

#endif // HealthMarkerManager_H
