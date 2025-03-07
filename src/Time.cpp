#include "Time.h"

int Time::minutes() const
{
    return m_minutes;
}

void Time::setMinutes(int newMinutes)
{
    if (m_minutes == newMinutes)
        return;
    m_minutes = newMinutes;
}

int Time::seconds() const
{
    return m_seconds;
}

void Time::setSeconds(int newSeconds)
{
    if (m_seconds == newSeconds)
        return;
    m_seconds = newSeconds;
}

int Time::hours() const
{
    return m_hours;
}

void Time::setHours(int newHours)
{
    if (m_hours == newHours)
        return;
    m_hours = newHours;
}
