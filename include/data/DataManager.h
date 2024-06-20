#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "FoodItem.h"
#include "Recipe.h"

#include <QDir>

class Exercise;

class DataManager
{
public:
    static void init();

    enum DataError {
        Success,
        Failure,
        NoOp
    };

    static DataError removeFood(int meal, QDate date, const FoodServing &food);
    static DataError saveFood(int meal, QDate date, const FoodServing &food);
    static QList<FoodServing> loadFoods(int meal, QDate date);

    static DataError removeRecipe(const Recipe &recipe);
    static DataError saveRecipe(const Recipe &recipe);
    static QList<Recipe> loadRecipes();

    static DataError saveExercises(QList<Exercise *> exercises, QDate date);
    static QList<Exercise *> loadExercises(QWidget *parent, QDate date);

    static DataError saveInfo(QString field, QVariant data);
    static QVariantMap loadInfo();
    static QVariant getInfo(const QString &field);

private:
    static QDir dataDir;

    static DataError addJsonObject(QFile &file, const QJsonObject &obj);
};

#endif // DATAMANAGER_H
