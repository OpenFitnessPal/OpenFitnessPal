#include "../include/NutritionManager.h"
#include "DataManager.h"
#include "FoodItem.h"

NutritionManager::NutritionManager(QObject *parent)
    : QObject{parent}
{}

NutrientUnion NutritionManager::getDailyNutrients(QDate date)
{
    QList<FoodServing> meal1 = DataManager::loadFoods(1, date);
    QList<FoodServing> meal2 = DataManager::loadFoods(2, date);
    QList<FoodServing> meal3 = DataManager::loadFoods(3, date);
    QList<FoodServing> meal4 = DataManager::loadFoods(4, date);
    QList<FoodServing> meal5 = DataManager::loadFoods(5, date);

    QList<FoodServing> meals = meal1 + meal2 + meal3 + meal4 + meal5;

    NutrientUnion nutrients;

    for (const FoodServing &food : meals) {
        nutrients += food.nutrients();
    }

    return nutrients;
}
