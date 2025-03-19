#include "data/HealthMarkerManager.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

HealthMarkerManager::HealthMarkerManager(QObject *parent)
    : DataManager{parent}
{
    m_filename = "health.json";
    m_useDate = true;
    m_nearest = true;
    m_modifiedFileName = "healthModified";
}

bool HealthMarkerManager::save(const QList<HealthMarker> &markers)
{
    QJsonArray arr;
    for (const HealthMarker &h : markers) {
        arr.append(h.toJson());
    }

    return write(arr);
}

QList<HealthMarker> HealthMarkerManager::load()
{
    QJsonArray arr = readArray();

    m_markers.clear();

    for (QJsonValueConstRef ref : std::as_const(arr)) {
        HealthMarker marker = HealthMarker::fromJson(ref.toObject());
        m_markers.append(marker);
        emit dataChanged(marker.name, marker.value);
    }

    return m_markers;
}
