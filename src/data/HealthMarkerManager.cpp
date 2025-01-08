#include "data/HealthMarkerManager.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

HealthMarkerManager::HealthMarkerManager(QObject *parent)
    : QObject{parent}
{
    m_dir = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
}

bool HealthMarkerManager::set(const QString &field, const QVariant &data)
{
    QDir dir(m_dir);

    QFile f(dir.absoluteFilePath("health.json"));
    QJsonObject obj;

    if (!f.open(QIODevice::ReadOnly)) {
        return false;
    }

    obj = QJsonDocument::fromJson(f.readAll()).object();
    f.close();

    if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        return false;
    }

    obj.insert(field, data.toJsonValue());

    f.write(QJsonDocument(obj).toJson());
    f.close();

    return true;
}


QVariant HealthMarkerManager::get(const QString &field, const QVariant &defaultValue) const
{
    QDir dir(m_dir);

    QFile f(dir.absoluteFilePath("health.json"));
    QJsonObject obj;

    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return defaultValue;
    }

    obj = QJsonDocument::fromJson(f.readAll()).object();
    f.close();

    return obj.contains(field) ? obj.value(field) : defaultValue;
}
