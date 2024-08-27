#include "GoalManager.h"
#include "DataManager.h"

GoalManager::GoalManager(QObject *parent)
    : QObject{parent}
{}

void GoalManager::set(const QString &key, const QVariant &value) const
{
    DataManager::saveInfo(key, value);
}

QVariant GoalManager::get(const QString &key) const
{
    return DataManager::getInfo(key);
}
