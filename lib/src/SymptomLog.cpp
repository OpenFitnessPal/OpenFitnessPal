#include "../include/SymptomLog.h"

#include <QJsonObject>

SymptomLog::SymptomLog() {}

QTime SymptomLog::time() const
{
    return m_time;
}

void SymptomLog::setTime(const QTime &newTime)
{
    if (m_time == newTime)
        return;
    m_time = newTime;
}

QString SymptomLog::message() const
{
    return m_message;
}

void SymptomLog::setMessage(const QString &newMessage)
{
    if (m_message == newMessage)
        return;
    m_message = newMessage;
}

QJsonObject SymptomLog::toJson() const
{
    QJsonObject obj;
    obj.insert("time", m_time.toString("hh:mm"));
    obj.insert("message", m_message);
    return obj;
}

SymptomLog SymptomLog::fromJson(const QJsonObject &obj)
{
    SymptomLog s;
    s.setMessage(obj.value("message").toString());
    s.setTime(QTime::fromString(obj.value("time").toString(), "hh:mm"));
    return s;
}
