#include "DateManager.h"

QDateTime DateManager::date() const
{
    return m_date;
}

void DateManager::setDate(const QDateTime &newDate)
{
    if (m_date == newDate)
        return;
    m_date = newDate;

    emit dateChanged();
}

DateManager::DateManager(QObject *parent)
    : QObject{parent}
{
    m_date = QDateTime::currentDateTime();
}
