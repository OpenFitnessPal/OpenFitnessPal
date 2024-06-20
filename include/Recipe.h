#ifndef RECIPE_H
#define RECIPE_H

#include "FoodItem.h"
#include "NutrientUnion.h"

#include <QList>

class Recipe
{
public:
    Recipe();

    void addFood(const FoodServing &food);
    void removeFood(const FoodServing &food);
    QList<FoodServing> foods() const;

    NutrientUnion nutrients(double units);

    QString name() const;
    void setName(const QString &newName);

    QJsonObject toJson() const;
    static Recipe fromJson(const QJsonObject &obj);

    double servings() const;
    void setServings(double newServings);

private:
    QList<FoodServing> m_foods;

    double m_servings;

    QString m_name;
};

#endif // RECIPE_H
