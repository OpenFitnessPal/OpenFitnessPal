#ifndef MEALLOG_H
#define MEALLOG_H

#include <QWidget>

#include <OFP/FoodItem.h>

#include "data/DataManager.h"
#include "NutrientUnion.h"

namespace Ui {
class MealLog;
}

class FoodInfoWidget;

class MealLog : public QWidget
{
    Q_OBJECT

public:
    explicit MealLog(QWidget *parent = nullptr);
    ~MealLog();

    void setMealName(const QString &name);

    void setNumber(int newNumber);

    NutrientUnion getNutrients();

public slots:
    void addItem();
    void addFood(const FoodItem &item, const ServingSize &size, const double units);
    void addFood(const FoodServing &serving);

    void setDate(QDate date);

signals:
    void foodsChanged();

private:
    Ui::MealLog *ui;

    QList<FoodInfoWidget *> m_widgets;

    int m_number;
    QDate m_date;
    void reloadFood();
};

#endif // MEALLOG_H
