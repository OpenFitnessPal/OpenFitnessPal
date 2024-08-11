#ifndef DATAMANAGER_H
#define DATAMANAGER_H

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
    static DataError removeFood(int meal, QDate date, const FoodServing &food);
    static DataError saveFood(int meal, QDate date, const FoodServing &food);
    static DataError truncateSaveFoods(int meal, QDate date, const QList<FoodServing> &foods);
    static QList<FoodServing> loadFoods(int meal, QDate date);

    static DataError removeRecipe(const Recipe &recipe);
    static DataError saveRecipe(const Recipe &recipe);
    static DataError truncateSaveRecipes(const QList<Recipe> &recipes);
    static QList<Recipe> loadRecipes();
    static QList<Recipe> searchRecipes(const QString &query);

    static DataError removeExercise(const Exercise &exercise, const QDate &date);
    static DataError saveExercise(const Exercise &exercise, QDate date);
    static DataError truncateSaveExercises(const QList<Exercise> &exercises, QDate date);
    static QList<Exercise> loadExercises(QDate date);

    static DataError saveInfo(QString field, QVariant data);
    static QVariantMap loadInfo();
    static QVariant getInfo(const QString &field);

    static DataError mv(const QString &newPath);
    static void newPath (const QString &newPath);

private:
    static QDir dataDir;

    static DataError addJsonObject(QFile &file, const QJsonObject &obj);
};

#endif // DATAMANAGER_H
