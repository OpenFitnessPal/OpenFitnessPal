#include "items/MacroPreview.h"
#include "dialogs/NutrientDialog.h"
#include "ui_MacroPreview.h"

#include <data/DataManager.h>
#include <qscroller.h>

MacroPreview::MacroPreview(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::MacroPreview)
{
    ui->setupUi(this);

    ui->cals->setUnit("kcal");
    ui->cals->setName("Calories");
}

MacroPreview::~MacroPreview()
{
    delete ui;
}

void MacroPreview::setNutrients(const NutrientUnion &n)
{
    m_nutrients = n;

    int cals = DataManager::getInfo("calories").toInt();

    ui->cals->setTotal(n.calories());
    ui->cals->setTarget(cals);
}

void MacroPreview::mousePressEvent(QMouseEvent *e)
{
    QWidget::mousePressEvent(e);

    NutrientDialog *dialog = new NutrientDialog(m_nutrients, this);
    dialog->showMaximized();
}
