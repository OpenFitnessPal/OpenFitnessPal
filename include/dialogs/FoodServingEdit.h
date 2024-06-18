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
    explicit FoodServingEdit(const FoodItem &item, QWidget *parent = nullptr, const ServingSize &size = ServingSize{}, const double units = 1);
    ~FoodServingEdit();

public slots:
    void sendFood();
    void calcMacros();

signals:
    void foodReady(const FoodItem &item, const ServingSize &size, const double units);

private:
    Ui::FoodServingEdit *ui;

    const FoodItem m_item;
    QMap<QString, ServingSize> m_sizeMap;
};

#endif // FOODSERVINGEDIT_H
