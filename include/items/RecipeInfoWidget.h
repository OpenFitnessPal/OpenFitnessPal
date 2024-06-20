#ifndef RECIPEINFOWIDGET_H
#define RECIPEINFOWIDGET_H

#include "Recipe.h"
#include <QWidget>

namespace Ui {
class RecipeInfoWidget;
}

class RecipeInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RecipeInfoWidget(const Recipe &recipe, const double units = 1, QWidget *parent = nullptr);
    ~RecipeInfoWidget();

    Recipe recipe();

    double units() const;
    void setUnits(double newUnits);

    void updateLabels();

    void showDelete();

    void setRecipe(const Recipe &newRecipe);

public slots:
    void remove();

private:
    Ui::RecipeInfoWidget *ui;

    Recipe m_recipe;

    double m_units;

    void mouseReleaseEvent(QMouseEvent *e);

signals:
    void selected();
    void deleteRequested();
};

#endif // SEARCHITEMWIDGET_H
