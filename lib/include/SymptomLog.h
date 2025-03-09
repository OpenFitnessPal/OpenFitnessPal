#ifndef SYMPTOMLOG_H
#define SYMPTOMLOG_H

#include <QObject>
#include <QQmlEngine>
#include <QTime>

class SymptomLog
{
    Q_GADGET
    QML_VALUE_TYPE(symptomLog)
public:
    explicit SymptomLog();

    QTime time() const;
    void setTime(const QTime &newTime);

    QString message() const;
    void setMessage(const QString &newMessage);

    QJsonObject toJson() const;
    static SymptomLog fromJson(const QJsonObject &obj);

private:
    QTime m_time;
    QString m_message;

    Q_PROPERTY(QTime time READ time WRITE setTime FINAL)
    Q_PROPERTY(QString message READ message WRITE setMessage FINAL)
};

#endif // SYMPTOMLOG_H
