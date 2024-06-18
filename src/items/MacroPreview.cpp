#include "items/MacroPreview.h"
#include "ui_MacroPreview.h"

#include <data/DataManager.h>

MacroPreview::MacroPreview(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::MacroPreview)
{
    ui->setupUi(this);
}

MacroPreview::~MacroPreview()
{
    delete ui;
}

void MacroPreview::setNutrients(const NutrientUnion &n)
{
    int cals = DataManager::getInfo("calories").toInt();

    double targetCarbs = DataManager::getInfo("carbs").toDouble() / 100. * cals / 4.;
    double targetFat = DataManager::getInfo("fat").toDouble() / 100. * cals / 9.;
    double targetProtein = DataManager::getInfo("protein").toDouble() / 100. * cals / 4.;

    ui->carbTotal->setText(QString::number(n.carbs) + "g");
    ui->fatTotal->setText(QString::number(n.fat) + "g");
    ui->proteinTotal->setText(QString::number(n.protein) + "g");
    ui->calTotal->setText(QString::number(n.calories()) + "kcal");

    ui->carbTarget->setText(QString::number(targetCarbs) + "g");
    ui->fatTarget->setText(QString::number(targetFat) + "g");
    ui->proteinTarget->setText(QString::number(targetProtein) + "g");
    ui->calTarget->setText(QString::number(cals) + "kcal");

    ui->carbs->setValue(std::min(n.carbs / targetCarbs * 100.0, 100.0));
    ui->fat->setValue(std::min(n.fat / targetFat * 100.0, 100.0));
    ui->protein->setValue(std::min(n.protein / targetProtein * 100.0, 100.0));
    ui->cals->setValue(std::min(n.calories() / cals * 100.0, 100.0));
}
