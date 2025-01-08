#ifndef CARDIO_H
#define CARDIO_H

#include <QObject>
#include <QQmlEngine>

class Cardio : public QObject
{
    Q_OBJECT

    QML_VALUE_TYPE(cardio)
public:
    explicit Cardio(QObject *parent = nullptr);
    Cardio(const Cardio &other);

    Cardio operator=(const Cardio &other);

    int calories() const;
    void setCalories(int newCalories);

    double minutes() const;
    void setMinutes(double newMinutes);

    QString notes() const;
    void setNotes(const QString &newNotes);

    QJsonObject toJson() const;
    static Cardio fromJson(const QJsonObject &obj);

signals:
    void caloriesChanged();

    void minutesChanged();

    void notesChanged();

private:
    double m_minutes;
    int m_calories;
    QString m_notes;

    Q_PROPERTY(int calories READ calories WRITE setCalories NOTIFY caloriesChanged FINAL)
    Q_PROPERTY(double minutes READ minutes WRITE setMinutes NOTIFY minutesChanged FINAL)
    Q_PROPERTY(QString notes READ notes WRITE setNotes NOTIFY notesChanged FINAL)
};

bool operator==(const Cardio &a, const Cardio &b);

#endif // CARDIO_H
