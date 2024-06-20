#ifndef FOODSEARCH_H
#define FOODSEARCH_H

#include <QDialog>
#include "OFPManager.h"
#include "Recipe.h"
#include "items/FoodInfoWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class FoodSearch;
}
QT_END_NAMESPACE

class FoodSearch : public QDialog
{
    Q_OBJECT

public:
    FoodSearch(QWidget *parent = nullptr);
    ~FoodSearch();

public slots:
    void search();

signals:
    void itemSelected(const FoodServing &food);
    void recipeSelected(const Recipe &recipe, const double units);

private:
    Ui::FoodSearch *ui;

    OFPManager *m_manager;
    QList<QWidget *> m_widgets{};

    void addFood(const FoodItem &item);
    void addRecipe(const Recipe &recipe);
};
#endif // FOODSEARCH_H
