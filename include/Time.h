#ifndef TIME_H
#define TIME_H

#include <QQmlEngine>

class Time {
    Q_GADGET

    QML_VALUE_TYPE(time)

    int m_hours;
    int m_minutes;
    int m_seconds;

public:
    int hours() const;
    void setHours(int newHours);

    int minutes() const;
    void setMinutes(int newMinutes);

    int seconds() const;
    void setSeconds(int newSeconds);

private:
    Q_PROPERTY(int hours READ hours WRITE setHours FINAL)
    Q_PROPERTY(int minutes READ minutes WRITE setMinutes FINAL)
    Q_PROPERTY(int seconds READ seconds WRITE setSeconds FINAL)
};

Q_DECLARE_METATYPE(Time)

#endif // TIME_H
