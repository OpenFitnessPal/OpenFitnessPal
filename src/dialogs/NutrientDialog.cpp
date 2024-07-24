#include "dialogs/NutrientDialog.h"
#include "ui_NutrientDialog.h"

#include <data/DataManager.h>
#include <qscroller.h>

NutrientDialog::NutrientDialog(const NutrientUnion &n, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NutrientDialog)
{
    ui->setupUi(this);

    // this is cancer
    ui->calcium->setName("Calcium");
    ui->vitaminA->setName("Vitamin A");
    ui->vitaminC->setName("Vitamin C");
    ui->vitaminD->setName("Vitamin D");
    ui->iron->setName("Iron");

    ui->protein->setName("Protein");
    ui->carbs->setName("Carbs");
    ui->sugar->setName("Sugar");
    ui->fiber->setName("Fiber");
    ui->sat->setName("Saturated Fat");
    ui->mono->setName("Monounsaturated Fat");
    ui->poly->setName("Polyunsaturated Fat");
    ui->trans->setName("Trans Fat");
    ui->fat->setName("Total Fat");

    ui->cholesterol->setName("Cholesterol");
    ui->sodium->setName("Sodium");
    ui->potassium->setName("Potassium");

    ui->calcium->setUnit("%");
    ui->vitaminA->setUnit("%");
    ui->vitaminC->setUnit("%");
    ui->vitaminD->setUnit("%");
    ui->iron->setUnit("%");

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

    ui->carbs->setTarget(targetCarbs);
    ui->fat->setTarget(targetFat);
    ui->protein->setTarget(targetProtein);

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

    QScroller::grabGesture(ui->scrollArea, QScroller::LeftMouseButtonGesture);
}

NutrientDialog::~NutrientDialog()
{
    delete ui;
}
