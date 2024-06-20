#ifndef RECIPESPAGE_H
#define RECIPESPAGE_H

#include "Recipe.h"
#include "items/RecipeInfoWidget.h"

#include <QWidget>

namespace Ui {
class RecipesPage;
}

class RecipesPage : public QWidget
{
    Q_OBJECT

public:
    explicit RecipesPage(QWidget *parent = nullptr);
    ~RecipesPage();

public slots:
    void addItem();

    void addRecipe(const Recipe &recipe);
private:
    Ui::RecipesPage *ui;

    QList<RecipeInfoWidget *> m_widgets;
};

#endif // RECIPESPAGE_H
