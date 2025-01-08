#ifndef RECIPE_H
#define RECIPE_H

#include "FoodItem.h"
#include "NutrientUnion.h"

#include <QList>
#include <qqmlintegration.h>

class Recipe
{
    Q_GADGET
    Q_PROPERTY(QList<FoodServing> foods READ foods WRITE setFoods FINAL)
    Q_PROPERTY(double servings READ servings WRITE setServings FINAL)
    Q_PROPERTY(QString name READ name WRITE setName FINAL)
public:
    Recipe();

    void addFood(const FoodServing &food);
    void removeFood(const FoodServing &food);
    void setFoods(const QList<FoodServing> &foods);
    QList<FoodServing> foods() const;

    Q_INVOKABLE QList<FoodServing> asServings(double units);
    Q_INVOKABLE FoodServing asFood(double units);

    Q_INVOKABLE NutrientUnion nutrients(double units = 1);

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

Q_DECLARE_METATYPE(Recipe)

#endif // RECIPE_H
