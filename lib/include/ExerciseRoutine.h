#ifndef EXERCISEROUTINE_H
#define EXERCISEROUTINE_H

#include "Exercise.h"

#include <QList>
#include <QQmlEngine>

class ExerciseRoutine
{
    Q_GADGET
    Q_PROPERTY(QList<Exercise> exercises READ exercises WRITE setExercises FINAL)
    Q_PROPERTY(QString name READ name WRITE setName FINAL)
    Q_PROPERTY(QString notes READ notes WRITE setNotes FINAL)
public:
    ExerciseRoutine();
    ExerciseRoutine(const ExerciseRoutine &other);

    void addExercise(const Exercise &exercise);
    void removeExercise(const Exercise &exercise);
    void setExercises(const QList<Exercise> &exercises);
    QList<Exercise> exercises() const;

    QString name() const;
    void setName(const QString &newName);

    QString notes() const;
    void setNotes(const QString &newNotes);

    void extracted() const;
    QJsonObject toJson() const;
    static ExerciseRoutine fromJson(const QJsonObject &obj);

private:
    QList<Exercise> m_exercises;

    QString m_name;
    QString m_notes;
};

Q_DECLARE_METATYPE(ExerciseRoutine)


#endif // EXERCISEROUTINE_H
