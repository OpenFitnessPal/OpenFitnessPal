#ifndef RECIPESERVINGEDIT_H
#define RECIPESERVINGEDIT_H

#include "FoodItem.h"
#include "items/FoodInfoWidget.h"
#include <QDialog>
#include <Recipe.h>

namespace Ui {
class RecipeEdit;
}

class RecipeEdit : public QDialog
{
    Q_OBJECT

public:
    explicit RecipeEdit(QWidget *parent = nullptr, const Recipe &recipe = Recipe(), const double units = 1);
    ~RecipeEdit();

public slots:
    void sendRecipe();
    void addItem();
    void addFood(const FoodServing &food);

    void calcMacros();

signals:
    void recipeReady(const Recipe recipe);

private:
    Ui::RecipeEdit *ui;

    Recipe m_recipe;

    QList<FoodInfoWidget *> m_widgets;
};

#endif // FOODSERVINGEDIT_H
