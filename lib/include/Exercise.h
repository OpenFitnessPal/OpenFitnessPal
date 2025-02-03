#ifndef EXERCISE_H
#define EXERCISE_H

#include <QObject>
#include <QQmlEngine>

#include "ExerciseSet.h"

class Exercise : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QList<ExerciseSet> sets READ sets WRITE setSets NOTIFY setsChanged)

public:
    Exercise(QObject *parent = nullptr);
    Exercise(const Exercise &other);
    Exercise operator=(const Exercise &other);

    QString name() const;
    void setName(const QString &newName);

    QList<ExerciseSet> sets() const;
    void setSets(const QList<ExerciseSet> &newSets);

    QJsonObject toJson() const;
    static Exercise fromJson(const QJsonObject &obj);

    bool operator==(const Exercise &other) const;

public slots:
    void addSet();
    void addSet(int reps, int weight);
    void removeSet(int idx);
    void changeSet(int idx, int reps, int weight);

signals:
    void nameChanged();
    void setsChanged();

private:
    QString m_name;
    QList<ExerciseSet> m_sets;
};

Q_DECLARE_METATYPE(Exercise)
Q_DECLARE_METATYPE(QList<Exercise>)

#endif // EXERCISE_H
