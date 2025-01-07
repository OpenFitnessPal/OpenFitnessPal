#include "data/WeightManager.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

WeightManager::WeightManager(QObject *parent)
    : QObject{parent}
{
    QDir m_dir = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);

    resetDate();
}

QDate WeightManager::date() const
{
    return m_date;
}

void WeightManager::setDate(const QDate &newDate)
{
    if (m_date == newDate)
        return;
    m_date = newDate;
    emit dateChanged();
}

void WeightManager::resetDate()
{
    setDate(QDate::currentDate());
}

bool WeightManager::set(const QVariant &weight)
{
    QDir dir(m_dir);
    mkDate(dir);

    QFile f(dir.absoluteFilePath("weight"));
    if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        return false;
    }

    f.write(weight.toByteArray());
    f.close();

    return true;
}


QVariant WeightManager::get() const
{
    QDir dir(m_dir);

    mkDate(dir);

    QFile f(dir.absoluteFilePath("weight"));

    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return 135;
    }

    QVariant weight = f.readAll().toDouble();

    f.close();

    return weight;
}

bool WeightManager::mkDate(QDir &dir) const {
    QString dateString = m_date.toString("MM-dd-yyyy");

    if (!dir.mkpath(dateString)) {
        return false;
    }

    dir.cd(dateString);
    return true;
}
