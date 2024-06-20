#include "dialogs/RecipeEdit.h"

#include "ui_RecipeEdit.h"

#include "dialogs/FoodServingEdit.h"

#include <dialogs/FoodSearch.h>

RecipeEdit::RecipeEdit(QWidget *parent, const Recipe &recipe, const double units)
    : QDialog(parent)
    , ui(new Ui::RecipeEdit)
{
    ui->setupUi(this);

    ui->name->setText(recipe.name());
    ui->servings->setValue(recipe.servings() * units);

    for (const FoodServing &serving : recipe.foods()) {
        addFood(serving);
    }
}

RecipeEdit::~RecipeEdit()
{
    delete ui;
}

void RecipeEdit::addFood(const FoodServing &serving)
{
    FoodInfoWidget *food = new FoodInfoWidget(serving, this);
    food->showDelete();
    m_widgets.append(food);

    m_recipe.addFood(serving);

    connect(food, &FoodInfoWidget::selected, this, [this, food] {
        FoodServingEdit *edit = new FoodServingEdit(food->food(), this);
        edit->show();

        connect(edit, &FoodServingEdit::foodReady, this, [this, food](const FoodServing &serving) {
            m_recipe.removeFood(food->food());
            food->setFood(serving);
            m_recipe.addFood(serving);

            food->updateLabels();
            calcMacros();
        });
    });

    connect(food, &FoodInfoWidget::deleteRequested, this, [this, food] {
        m_recipe.removeFood(food->food());

        ui->foods->removeWidget(food);
        m_widgets.removeOne(food);
        food->deleteLater();

        calcMacros();
    });

    calcMacros();

    ui->foods->addWidget(food);
}

void RecipeEdit::calcMacros() {
    NutrientUnion n;

    for (const FoodInfoWidget *w : m_widgets) {
        FoodServing s = w->food();
        double mult = s.size.multiplier(s.units);

        n += s.item.nutrients() * mult;
    }

    ui->carbs->setText(QString::number(n.carbs) + "g");
    ui->fat->setText(QString::number(n.fat) + "g");
    ui->protein->setText(QString::number(n.protein) + "g");
    ui->calories->setText(QString::number(n.calories()));
}

void RecipeEdit::sendRecipe() {
    m_recipe.setName(ui->name->text());
    m_recipe.setServings(ui->servings->value());

    emit recipeReady(m_recipe);
    accept();
}

void RecipeEdit::addItem()
{
    FoodSearch *search = new FoodSearch(this);
    search->show();

    connect(search, &FoodSearch::itemSelected, this, [this](const FoodServing &food) {
        addFood(food);
    });
}
