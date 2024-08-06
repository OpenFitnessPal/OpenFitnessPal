#include "GoalManager.h"
#include "DataManager.h"

GoalManager::GoalManager(QObject *parent)
    : QObject{parent}
{}

void GoalManager::set(const QString &key, const QVariant &value)
{
    DataManager::saveInfo(key, value);
}

QVariant GoalManager::get(const QString &key)
{
    return DataManager::getInfo(key);
}
