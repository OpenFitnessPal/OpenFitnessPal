#include "data/HealthMarkerManager.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

HealthMarkerManager::HealthMarkerManager(QObject *parent)
    : DataManager{parent}
{
    // TOOD: this is custom
}

bool HealthMarkerManager::set(const QString &field, const QVariant &data)
{
    QDir dir(m_dir);
    mkDate(dir);

    QFile f(dir.absoluteFilePath("health.json"));
    QJsonObject obj;

    if (!f.open(QIODevice::ReadOnly)) {
        return createBlankJson(f).empty();
    }

    obj = QJsonDocument::fromJson(f.readAll()).object();
    f.close();

    if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        return false;
    }

    obj.insert(field, data.toJsonValue());

    f.write(QJsonDocument(obj).toJson());
    f.close();

    emit dataChanged(field, data);

    return true;
}

QVariant HealthMarkerManager::get(const QString &field, const QVariant &defaultValue)
{
    QDir dir(m_dir);
    mkDate(dir);

    QFile f(dir.absoluteFilePath("health.json"));
    QJsonObject obj;

    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        createBlankJson(f);
        return defaultValue;
    }

    obj = QJsonDocument::fromJson(f.readAll()).object();
    f.close();

    return obj.contains(field) ? obj.value(field) : defaultValue;
}

bool HealthMarkerManager::remove(const QString &field)
{
    QDir dir(m_dir);
    mkDate(dir);

    QFile f(dir.absoluteFilePath("health.json"));
    QJsonObject obj;

    if (!f.open(QIODevice::ReadOnly)) {
        return createBlankJson(f).empty();
    }

    obj = QJsonDocument::fromJson(f.readAll()).object();
    f.close();

    if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        return false;
    }

    obj.remove(field);

    f.write(QJsonDocument(obj).toJson());
    f.close();

    return true;
}

QList<HealthMarker> HealthMarkerManager::getCurrentMarkers()
{
    QDir dir(m_dir);

    QFile f(dir.absoluteFilePath("health.json"));
    QJsonObject obj;

    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        obj = createBlankJson(f);
    } else {
        obj = QJsonDocument::fromJson(f.readAll()).object();
        f.close();
    }

    QList<HealthMarker> list;

    for (const QString &key : obj.keys()) {
        HealthMarker marker;
        marker.name = key;
        marker.value = obj.value(key);
        list.append(marker);
    }

    return list;
}


QList<QVariant> HealthMarkerManager::markers()
{
    if (m_markers.empty()) {
        QDir dir(m_dir);

        QFile f(dir.absoluteFilePath("healthOptions.json"));
        QJsonArray arr;

        if (!f.open(QIODevice::ReadOnly)) {
            return m_markers;
        }

        arr = QJsonDocument::fromJson(f.readAll()).array();
        f.close();

        m_markers = arr.toVariantList();
    }

    return m_markers;
}

void HealthMarkerManager::setMarkers(const QList<QVariant> &newMarkers)
{
    if (m_markers == newMarkers)
        return;
    m_markers = newMarkers;
    emit markersChanged();

    QDir dir(m_dir);

    QFile f(dir.absoluteFilePath("healthOptions.json"));

    if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        return;
    }

    QJsonArray arr = QJsonArray::fromVariantList(m_markers);

    f.write(QJsonDocument(arr).toJson());
    f.close();
}

QJsonObject HealthMarkerManager::createBlankJson(QFile &f) {
    QJsonObject obj{};

    if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        return obj;
    }

    QVariantList markers = this->markers();

    for (const QVariant &v : std::as_const(markers)) {
        obj.insert(v.toString(), QJsonValue());
    }

    f.write(QJsonDocument(obj).toJson());
    f.close();

    return obj;
}
