#ifndef FOODSERVINGEDIT_H
#define FOODSERVINGEDIT_H

#include "FoodItem.h"
#include <QDialog>

namespace Ui {
class FoodServingEdit;
}

class FoodServingEdit : public QDialog
{
    Q_OBJECT

public:
    FoodServingEdit(const FoodServing &food, QWidget *parent = nullptr);
    ~FoodServingEdit();

public slots:
    void sendFood();
    void calcMacros();

signals:
    void foodReady(const FoodServing &food);

private:
    Ui::FoodServingEdit *ui;

    const FoodItem m_item;
    QMap<QString, ServingSize> m_sizeMap;
};

#endif // FOODSERVINGEDIT_H
