#ifndef NUTRIENTDIALOG_H
#define NUTRIENTDIALOG_H

#include "NutrientUnion.h"
#include <QDialog>

namespace Ui {
class NutrientDialog;
}

class NutrientDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NutrientDialog(const NutrientUnion &n, QWidget *parent = nullptr);
    ~NutrientDialog();

private:
    Ui::NutrientDialog *ui;
};

#endif // NUTRIENTDIALOG_H
