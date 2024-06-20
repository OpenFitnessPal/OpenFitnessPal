#include "dialogs/RecipeAdd.h"

#include "ui_RecipeAdd.h"

#include <dialogs/FoodSearch.h>

RecipeAdd::RecipeAdd(QWidget *parent, const Recipe &recipe)
    : QDialog(parent)
    , ui(new Ui::RecipeAdd)
    , m_recipe(recipe)
{
    ui->setupUi(this);

    ui->name->setText(recipe.name());
    ui->servings->setValue(recipe.servings());
}

RecipeAdd::~RecipeAdd()
{
    delete ui;
}

void RecipeAdd::calcMacros(double units) {
    NutrientUnion n = m_recipe.nutrients(units / m_recipe.servings());

    ui->carbs->setText(QString::number(n.carbs) + "g");
    ui->fat->setText(QString::number(n.fat) + "g");
    ui->protein->setText(QString::number(n.protein) + "g");
    ui->calories->setText(QString::number(n.calories()));
}

void RecipeAdd::sendRecipe() {
    emit recipeReady(m_recipe, ui->servings->value());
    accept();
}
