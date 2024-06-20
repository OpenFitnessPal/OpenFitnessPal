#include "Recipe.h"

#include <QJsonArray>

Recipe::Recipe() {}

void Recipe::addFood(const FoodServing &food)
{
    m_foods.append(food);
}

void Recipe::removeFood(const FoodServing &food)
{
    m_foods.removeOne(food);
}

QList<FoodServing> Recipe::foods() const
{
    return m_foods;
}

NutrientUnion Recipe::nutrients(double units)
{
    NutrientUnion n;
    for (const FoodServing &serving : m_foods) {
        FoodItem f = serving.item;
        ServingSize s = serving.size;
        double u = serving.units;

        double mult = s.multiplier(u) * units;

        n += f.nutrients() * mult;
    }

    return n;
}

QString Recipe::name() const
{
    return m_name;
}

void Recipe::setName(const QString &newName)
{
    m_name = newName;
}

QJsonObject Recipe::toJson() const
{
    QJsonObject obj{};

    obj.insert("name", m_name);
    obj.insert("units", m_servings);

    QJsonArray foods;

    for (const FoodServing &food : m_foods) {
        foods.append(food.toJson());
    }

    obj.insert("foods", foods);

    return obj;
}

Recipe Recipe::fromJson(const QJsonObject &obj)
{
    Recipe recipe;

    recipe.setServings(obj.value("units").toDouble());
    recipe.setName(obj.value("name").toString());

    QJsonArray array = obj.value("foods").toArray();

    for (QJsonValueRef ref : array) {
        recipe.addFood(FoodServing::fromJson(ref.toObject()));
    }

    return recipe;
}

double Recipe::servings() const
{
    return m_servings;
}

void Recipe::setServings(double newServings)
{
    m_servings = newServings;
}
