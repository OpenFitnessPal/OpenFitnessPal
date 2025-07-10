#include "SymptomLogManager.h"

#include <QJsonArray>
#include <QJsonObject>

SymptomLogManager::SymptomLogManager(QObject *parent)
    : DataManager{parent}
{
    m_useDate = true;
    m_filename = "symptoms.json";
}

QList<SymptomLog> SymptomLogManager::load()
{
    QList<SymptomLog> symptoms;

    QJsonArray arr = readArray();

    for (QJsonValueConstRef ref : std::as_const(arr)) {
        symptoms.append(SymptomLog::fromJson(ref.toObject()));
    }

    return symptoms;
}

bool SymptomLogManager::save(const QList<SymptomLog> &symptoms)
{
    QJsonArray arr;

    for (const SymptomLog &s : symptoms) {
        arr.append(s.toJson());
    }

    return write(arr);
}
