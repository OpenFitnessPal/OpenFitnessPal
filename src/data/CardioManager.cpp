#include "data/CardioManager.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

CardioManager::CardioManager(QObject *parent)
    : DataManager{parent}
{
    m_filename = "cardio.json";
    m_useDate = true;
}

QList<Cardio> CardioManager::load()
{
    QList<Cardio> exercises{};

    QJsonArray arr = readArray();

    for (QJsonValueConstRef ref : std::as_const(arr)) {
        exercises.append(Cardio::fromJson(ref.toObject()));
    }

    return exercises;
}

bool CardioManager::save(const QList<Cardio> &exercises)
{
    QJsonArray arr;

    for (const Cardio & ex : exercises) {
        arr.append(ex.toJson());
    }

    return write(arr);
}
