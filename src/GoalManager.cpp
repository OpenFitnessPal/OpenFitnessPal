#include "GoalManager.h"
#include "DataManager.h"

GoalManager::GoalManager(QObject *parent)
    : QObject{parent}
{}

void GoalManager::setValue(const QString &key, const QVariant &value)
{
    DataManager::saveInfo(key, value);
}

QVariant GoalManager::getValue(const QString &key)
{
    return DataManager::getInfo(key);
}
