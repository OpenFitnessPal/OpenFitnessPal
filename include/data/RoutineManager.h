#ifndef ROUTINEMANAGER_H
#define ROUTINEMANAGER_H

#include <ExerciseRoutine.h>
#include <QObject>
#include <QQmlEngine>

class RoutineManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    QString m_file;

    QList<ExerciseRoutine> m_routines;
public:
    RoutineManager(QObject *parent = nullptr);

    Q_INVOKABLE bool save(const QList<ExerciseRoutine> &outines);
    Q_INVOKABLE QList<ExerciseRoutine> load();
    Q_INVOKABLE QList<ExerciseRoutine> search(const QString &query);
};

#endif // ROUTINEMANAGER_H
