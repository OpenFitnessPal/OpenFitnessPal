#ifndef MEALLOG_H
#define MEALLOG_H

#include <QWidget>

#include <OFP/FoodItem.h>

#include "data/DataManager.h"

namespace Ui {
class MealLog;
}

class MealLog : public QWidget
{
    Q_OBJECT

public:
    explicit MealLog(QWidget *parent = nullptr);
    ~MealLog();

    void setMealName(const QString &name);

    void setNumber(int newNumber);

public slots:
    void addItem();
    void addFood(const FoodItem &item, const ServingSize &size, const double units);
    void addFood(const FoodServing &serving);

    void setDate(QDate date);

private:
    Ui::MealLog *ui;

    QList<QWidget *> m_widgets;

    int m_number;
    QDate m_date;
    void reloadFood();
};

#endif // MEALLOG_H
