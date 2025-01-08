#ifndef HealthMarkerManager_H
#define HealthMarkerManager_H

#include <QDir>
#include <QObject>
#include <QQmlEngine>

class HealthMarkerManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    QDir m_dir;
public:
    HealthMarkerManager(QObject *parent = nullptr);

    Q_INVOKABLE bool set(const QString &field, const QVariant &data);
    Q_INVOKABLE QVariant get(const QString &key, const QVariant &defaultValue) const;
};

#endif // HealthMarkerManager_H
