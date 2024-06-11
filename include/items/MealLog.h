#ifndef MEALLOG_H
#define MEALLOG_H

#include <QWidget>

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

public slots:
    void addItem();

private:
    Ui::MealLog *ui;
};

#endif // MEALLOG_H
