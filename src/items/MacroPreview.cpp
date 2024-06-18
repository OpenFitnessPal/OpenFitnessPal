#include "items/MacroPreview.h"
#include "dialogs/NutrientDialog.h"
#include "ui_MacroPreview.h"

#include <data/DataManager.h>

MacroPreview::MacroPreview(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::MacroPreview)
{
    ui->setupUi(this);

    ui->cals->setUnit("kcal");
    ui->carbs->setUnit("g");
    ui->fat->setUnit("g");
    ui->protein->setUnit("g");
}

MacroPreview::~MacroPreview()
{
    delete ui;
}

void MacroPreview::setNutrients(const NutrientUnion &n)
{
    m_nutrients = n;

    int cals = DataManager::getInfo("calories").toInt();

    double targetCarbs = DataManager::getInfo("carbs").toDouble() / 100. * cals / 4.;
    double targetFat = DataManager::getInfo("fat").toDouble() / 100. * cals / 9.;
    double targetProtein = DataManager::getInfo("protein").toDouble() / 100. * cals / 4.;

    ui->carbs->setTotal(n.carbs);
    ui->fat->setTotal(n.fat);
    ui->protein->setTotal(n.protein);
    ui->cals->setTotal(n.calories());

    ui->carbs->setTarget(targetCarbs);
    ui->fat->setTarget(targetFat);
    ui->protein->setTarget(targetProtein);
    ui->cals->setTarget(cals);
}

void MacroPreview::mousePressEvent(QMouseEvent *e)
{
    QWidget::mousePressEvent(e);

    NutrientDialog *dialog = new NutrientDialog(m_nutrients, this);
    dialog->show();
}
