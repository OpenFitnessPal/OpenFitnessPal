#include "Recipe.h"

#include <QJsonArray>

Recipe::Recipe() {
    m_foods = {};
    m_name = "";
    m_servings = 1;
}

void Recipe::addFood(const FoodServing &food)
{
    m_foods.append(food);
}

void Recipe::removeFood(const FoodServing &food)
{
    m_foods.removeOne(food);
}

void Recipe::setFoods(const QList<FoodServing> &foods)
{
    m_foods = foods;
}

QList<FoodServing> Recipe::foods() const
{
    return m_foods;
}

QList<FoodServing> Recipe::asServings(double units)
{
    QList<FoodServing> foods;
    for (FoodServing food : m_foods) {
        food.units *= units / m_servings;

        foods.append(food);
    }

    return foods;
}

FoodServing Recipe::asFood(double units)
{
    FoodServing food;

    food.units = units;
    food.sizeIdx = 0;

    FoodItem item;
    item.addServingSize(ServingSize(1 / m_servings, "Servings", 1.0));
    item.setName(m_name);
    item.setBrand("Recipe");

    NutrientUnion n;
    for (FoodServing &food : m_foods) {
        n += food.nutrients();
    }

    item.setNutrients(n);

    food.item = item;

    return food;
}

NutrientUnion Recipe::nutrients(double units)
{
    NutrientUnion n;
    for (const FoodServing &serving : m_foods) {
        FoodItem f = serving.item;
        ServingSize s = serving.size();
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
