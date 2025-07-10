#ifndef EXERCISEMANAGER_H
#define EXERCISEMANAGER_H

#include "DataManager.h"

#include <QObject>
#include <QDateTime>

#include <Exercise.h>
#include <QDir>

class ExerciseManager : public DataManager
{
    Q_OBJECT
public:
    ExerciseManager(QObject *parent);

    Q_INVOKABLE QList<Exercise> load();
    Q_INVOKABLE bool save(const QList<Exercise> &exercises);
};

#endif // EXERCISEMANAGER_H
