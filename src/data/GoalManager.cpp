#include "data/GoalManager.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

GoalManager::GoalManager(QObject *parent)
    : QObject{parent}
{
    QDir m_dir = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);

    resetDate();
}

QDate GoalManager::date() const
{
    return m_date;
}

void GoalManager::setDate(const QDate &newDate)
{
    if (m_date == newDate)
        return;
    m_date = newDate;
    emit dateChanged();
}

void GoalManager::resetDate()
{
    setDate(QDate::currentDate());
}

bool GoalManager::set(const QString &field, const QVariant &data)
{
    QDir dir(m_dir);
    mkDate(dir);

    QFile f(dir.absoluteFilePath("goals.json"));
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


QVariant GoalManager::get(const QString &field, const QVariant &defaultValue) const
{
    QDir dir(m_dir);

    mkDate(dir);

    QFile f(dir.absoluteFilePath("goals.json"));
    QJsonObject obj;

    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return defaultValue;
    }

    obj = QJsonDocument::fromJson(f.readAll()).object();
    f.close();

    return obj.contains(field) ? obj.value(field) : defaultValue;
}

bool GoalManager::mkDate(QDir &dir) const {
    QString dateString = m_date.toString("MM-dd-yyyy");

    if (!dir.mkpath(dateString)) {
        return false;
    }

    dir.cd(dateString);
    return true;
}
