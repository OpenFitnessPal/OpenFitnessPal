#include "data/WeightManager.h"

#include <QDirIterator>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

WeightManager::WeightManager(QObject *parent)
    : DataManager(parent)
{
    m_useDate = true;
    m_filename = "weight";
    m_nearest = true;
    m_modifiedFileName = "weightModified";

    connect(this, &DataManager::dateChanged, this, &WeightManager::update);
}

bool WeightManager::set(const int weight)
{
    m_weight = weight;
    bool ok = write(QByteArray::number(weight));

    emit weightChanged();

    return ok;
}

int WeightManager::get(bool force)
{
    if (m_weight != -1 && !force) {
        return m_weight;
    }

    auto data = read();
    if (data.isEmpty()) {
        return m_weight == -1 ? 135 : m_weight;
    }

    m_weight = data.toInt();
    return m_weight;
}

void WeightManager::update()
{
    get(true);
    emit weightChanged();
}
