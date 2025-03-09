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
}

bool WeightManager::set(const int weight)
{
    bool ok = write(QByteArray::number(weight));
    qDebug() << "weight changed to" << weight << ok;

    emit weightChanged();

    return ok;
}


int WeightManager::get()
{
    qDebug() << "weight read as" << read();
    return read().toInt();
}
