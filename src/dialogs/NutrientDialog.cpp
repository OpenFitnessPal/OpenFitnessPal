#include "dialogs/NutrientDialog.h"
#include "ui_NutrientDialog.h"

#include <data/DataManager.h>

NutrientDialog::NutrientDialog(const NutrientUnion &n, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NutrientDialog)
{
    ui->setupUi(this);

    ui->calcium->setUnit("%");
    ui->vitaminA->setUnit("%");
    ui->vitaminC->setUnit("%");
    ui->vitaminD->setUnit("%");
    ui->iron->setUnit("%");

    ui->protein->setUnit("g");
    ui->carbs->setUnit("g");
    ui->sugar->setUnit("g");
    ui->fiber->setUnit("g");
    ui->sat->setUnit("g");
    ui->mono->setUnit("g");
    ui->poly->setUnit("g");
    ui->trans->setUnit("g");
    ui->fat->setUnit("g");

    ui->cholesterol->setUnit("mg");
    ui->sodium->setUnit("mg");
    ui->potassium->setUnit("mg");

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

    double target;
    double total;

#define DIFF(shortname, longname) \
    ui->shortname->setTotal(n.longname); \
    ui->shortname->setTarget(DataManager::getInfo(#shortname).toDouble());

#define SAME(name) DIFF(name, name);

    SAME(calcium)
    SAME(iron)
    SAME(vitaminA)
    SAME(vitaminC)
    SAME(vitaminD)
    SAME(cholesterol)
    SAME(sodium)
    SAME(potassium)
    SAME(fiber)
    SAME(sugar)

    DIFF(sat, satFat)
    DIFF(mono, monoFat)
    DIFF(poly, polyFat)
    DIFF(trans, transFat)

#undef DIFF
#undef SAME
}

NutrientDialog::~NutrientDialog()
{
    delete ui;
}
