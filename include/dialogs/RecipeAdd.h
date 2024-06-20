#ifndef RECIPEADDEDIT_H
#define RECIPEADDEDIT_H

#include <QDialog>
#include <Recipe.h>

namespace Ui {
class RecipeAdd;
}

class RecipeAdd : public QDialog
{
    Q_OBJECT

public:
    explicit RecipeAdd(QWidget *parent = nullptr, const Recipe &recipe = Recipe());
    ~RecipeAdd();

public slots:
    void sendRecipe();

    void calcMacros(double units);

signals:
    void recipeReady(const Recipe &recipe, const double units);

private:
    Ui::RecipeAdd *ui;

    Recipe m_recipe;
};

#endif // FOODSERVINGEDIT_H
