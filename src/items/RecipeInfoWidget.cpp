#include "items/RecipeInfoWidget.h"
#include "ui_RecipeInfoWidget.h"

#include <QDesktopServices>
#include <QMouseEvent>

// TODO: improve touch control
RecipeInfoWidget::RecipeInfoWidget(const Recipe &recipe, const double units, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RecipeInfoWidget)
    , m_recipe(recipe)
    , m_units(units)
{
    ui->setupUi(this);
    ui->remove->setHidden(true);

    updateLabels();
}

RecipeInfoWidget::~RecipeInfoWidget()
{
    delete ui;
}

Recipe RecipeInfoWidget::recipe()
{
    return m_recipe;
}

void RecipeInfoWidget::updateLabels() {
    ui->brand->setText(QString::number(m_units * m_recipe.servings()) + " servings");
    ui->cals->setText(QString::number(m_recipe.nutrients(m_units).calories()) + "kcal");
    ui->food->setText(m_recipe.name());
}

void RecipeInfoWidget::showDelete()
{
    ui->remove->setHidden(false);
}

void RecipeInfoWidget::remove()
{
    emit deleteRequested();
}

void RecipeInfoWidget::setRecipe(const Recipe &newRecipe)
{
    m_recipe = newRecipe;
    updateLabels();
}

void RecipeInfoWidget::mouseReleaseEvent(QMouseEvent *e) {
    emit selected();
}

double RecipeInfoWidget::units() const
{
    return m_units;
}

void RecipeInfoWidget::setUnits(double newUnits)
{
    m_units = newUnits;
    updateLabels();
}
