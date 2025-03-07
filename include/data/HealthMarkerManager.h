#ifndef HealthMarkerManager_H
#define HealthMarkerManager_H

#include <QDir>
#include <QObject>
#include <QQmlEngine>

typedef struct HealthMarker {
    QString name;
    QVariant value;
} HealthMarker;

class HealthMarkerManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    QDateTime m_date;
    QDir m_dir;
    QList<QVariant> m_markers;
public:
    HealthMarkerManager(QObject *parent = nullptr);

    Q_INVOKABLE bool set(const QString &field, const QVariant &data);
    Q_INVOKABLE QVariant get(const QString &key, const QVariant &defaultValue);
    bool remove(const QString &field);

    QList<HealthMarker> getCurrentMarkers();

    QList<QVariant> markers();
    void setMarkers(const QList<QVariant> &newMarkers);

    QDateTime date() const;
    void setDate(const QDateTime &newDate);

signals:
    void markersChanged();

    void dataChanged(const QString &name, const QVariant &data);
    void dateChanged();

private:
    Q_PROPERTY(QList<QVariant> markers READ markers WRITE setMarkers NOTIFY markersChanged FINAL)
    QJsonObject createBlankJson(QFile &f);
    bool mkDate(QDir &dir);
    Q_PROPERTY(QDateTime date READ date WRITE setDate NOTIFY dateChanged FINAL)
};

#endif // HealthMarkerManager_H
