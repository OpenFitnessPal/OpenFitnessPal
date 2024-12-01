#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "ExerciseRoutine.h"
#include "FoodItem.h"
#include "Recipe.h"
#include "qjsvalue.h"
#include "qqmlintegration.h"

#include <QDir>

class Exercise;

class DataManager
{
public:
    static void init ();

    enum DataError {
        Success,
        Failure,
        NoOp
    };

public:
    static DataError truncateSaveFoods(int meal, QDate date, const QList<FoodServing> &foods);
    static QList<FoodServing> loadFoods(int meal, QDate date);

    static DataError truncateSaveRecipes(const QList<Recipe> &recipes);
    static QList<Recipe> loadRecipes();
    static QList<Recipe> searchRecipes(const QString &query);

    static DataError truncateSaveRoutines(const QList<ExerciseRoutine> &outines);
    static QList<ExerciseRoutine> loadRoutines();
    static QList<ExerciseRoutine> searchRoutines(const QString &query);

    static DataError truncateSaveExercises(const QList<Exercise> &exercises, QDate date);
    static QList<Exercise> loadExercises(QDate date);

    static DataError saveInfo(QString field, QVariant data);
    static QVariantMap loadInfo();
    static QVariant getInfo(const QString &field, const QVariant &defaultValue);

    static DataError mv(const QString &newPath);
    static void newPath (const QString &newPath);

private:
    static QDir dataDir;
};

#endif // DATAMANAGER_H
