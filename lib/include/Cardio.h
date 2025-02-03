#ifndef CARDIO_H
#define CARDIO_H

#include <QObject>
#include <QQmlEngine>

class Cardio : public QObject
{
    Q_OBJECT
public:
    explicit Cardio(QObject *parent = nullptr);
    Cardio(const Cardio &other);

    Cardio operator=(const Cardio &other);

    int calories() const;
    void setCalories(int newCalories);

    double minutes() const;
    void setMinutes(double newMinutes);

    QString name() const;
    void setName(const QString &newName);

    QJsonObject toJson() const;
    static Cardio fromJson(const QJsonObject &obj);

signals:
    void caloriesChanged();

    void minutesChanged();

    void nameChanged();

private:
    double m_minutes;
    int m_calories;
    QString m_name;

    Q_PROPERTY(int calories READ calories WRITE setCalories NOTIFY caloriesChanged FINAL)
    Q_PROPERTY(double minutes READ minutes WRITE setMinutes NOTIFY minutesChanged FINAL)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
};

bool operator==(const Cardio &a, const Cardio &b);

#endif // CARDIO_H
