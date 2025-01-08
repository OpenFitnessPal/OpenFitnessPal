#include "data/CardioManager.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

CardioManager::CardioManager(QObject *parent)
    : QObject{parent}
{
    resetDate();
    m_dir = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
}

QDate CardioManager::date() const
{
    return m_date;
}

void CardioManager::setDate(const QDate &newDate)
{
    if (m_date == newDate)
        return;
    m_date = newDate;
    emit dateChanged();
}

void CardioManager::resetDate()
{
    setDate(QDate::currentDate());
}

QList<Cardio> CardioManager::load()
{
    QList<Cardio> exercises{};
    QDir dir(m_dir);

    mkDate(dir);

    QFile file(dir.absoluteFilePath("cardio.json"));

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return exercises;
    }

    QByteArray data = file.readAll();

    file.close();

    QJsonArray arr = QJsonDocument::fromJson(data).array();

    for (const QJsonValueRef ref : arr) {
        exercises.append(Cardio::fromJson(ref.toObject()));
    }

    return exercises;
}

bool CardioManager::save(const QList<Cardio> &exercises)
{
    QDir dir(m_dir);

    mkDate(dir);

    QFile file(dir.absoluteFilePath("cardio.json"));

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        return false;
    }

    QJsonArray arr;

    for (const Cardio & ex : exercises) {
        arr.append(ex.toJson());
    }

    file.write(QJsonDocument(arr).toJson());

    return true;
}

bool CardioManager::mkDate(QDir &dir) {
    QString dateString = m_date.toString("MM-dd-yyyy");

    if (!dir.mkpath(dateString)) {
        return false;
    }

    dir.cd(dateString);
    return true;
}
