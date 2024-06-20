#ifndef SEARCHITEMWIDGET_H
#define SEARCHITEMWIDGET_H

#include "FoodItem.h"
#include <QWidget>

namespace Ui {
class FoodInfoWidget;
}

class FoodInfoWidget : public QWidget
{
    Q_OBJECT

public:
    FoodInfoWidget(const FoodServing &food, QWidget *parent = nullptr);
    ~FoodInfoWidget();

    void updateLabels();

    void showDelete();

    FoodServing food() const;
    void setFood(const FoodServing &newServing);

public slots:
    void remove();

private:
    Ui::FoodInfoWidget *ui;

    FoodServing m_food;

    void mouseReleaseEvent(QMouseEvent *e);

signals:
    void selected();
    void deleteRequested();
};

#endif // SEARCHITEMWIDGET_H
