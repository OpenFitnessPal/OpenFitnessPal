#include "pages/GoalsPage.h"
#include "data/DataManager.h"
#include "ui_GoalsPage.h"

#include <QMessageBox>

// TODO: save everything upon startup
GoalsPage::GoalsPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GoalsPage)
{
    ui->setupUi(this);

    QVariantMap data = DataManager::loadInfo();

#define INT_SPINBOX(name) if (data.contains(#name)) ui->name->setValue(data.value(#name).toInt()); \
    else DataManager::saveInfo(#name, ui->name->value());

    INT_SPINBOX(carbs)
    INT_SPINBOX(fat)
    INT_SPINBOX(protein)
    INT_SPINBOX(fiber)
    INT_SPINBOX(sugar)
    INT_SPINBOX(sat)
    INT_SPINBOX(mono)
    INT_SPINBOX(poly)
    INT_SPINBOX(trans)
    INT_SPINBOX(iron)
    INT_SPINBOX(potassium)
    INT_SPINBOX(sodium)
    INT_SPINBOX(vitaminA)
    INT_SPINBOX(vitaminC)
    INT_SPINBOX(vitaminD)
    INT_SPINBOX(cholesterol)
    INT_SPINBOX(calcium)
    INT_SPINBOX(calories)
#undef INT_SPINBOX

    if (data.contains("weight")) ui->weight->setValue(data.value("weight").toDouble());
    if (data.contains("goal")) ui->goal->setCurrentIndex(data.value("goal").toInt());

    m_first = false;
}

GoalsPage::~GoalsPage()
{
    delete ui;
}

void GoalsPage::carbsChanged(const int value) {
    if (m_first) return;
    verifyMacros();
}

void GoalsPage::fatChanged(const int value) {
    if (m_first) return;
    verifyMacros();
}

void GoalsPage::proteinChanged(const int value) {
    if (m_first) return;
    verifyMacros();
}

void GoalsPage::fiberChanged(const int value) {
    if (m_first) return;
    DataManager::saveInfo("fiber", value);
}

void GoalsPage::sugarChanged(const int value) {
    if (m_first) return;
    DataManager::saveInfo("sugar", value);
}

void GoalsPage::satChanged(const int value) {
    if (m_first) return;
    DataManager::saveInfo("sat", value);
}

void GoalsPage::monoChanged(const int value) {
    if (m_first) return;
    DataManager::saveInfo("mono", value);
}

void GoalsPage::polyChanged(const int value) {
    if (m_first) return;
    DataManager::saveInfo("poly", value);
}

void GoalsPage::transChanged(const int value) {
    if (m_first) return;
    DataManager::saveInfo("trans", value);
}

void GoalsPage::calciumChanged(const int value) {
    if (m_first) return;
    DataManager::saveInfo("calcium", value);
}

void GoalsPage::ironChanged(const int value) {
    if (m_first) return;
    DataManager::saveInfo("iron", value);
}

void GoalsPage::vitaminAChanged(const int value) {
    if (m_first) return;
    DataManager::saveInfo("vitaminA", value);
}

void GoalsPage::vitaminCChanged(const int value) {
    if (m_first) return;
    DataManager::saveInfo("vitaminC", value);
}

void GoalsPage::vitaminDChanged(const int value) {
    if (m_first) return;
    DataManager::saveInfo("vitaminD", value);
}

void GoalsPage::sodiumChanged(const int value) {
    if (m_first) return;
    DataManager::saveInfo("sodium", value);
}

void GoalsPage::potassiumChanged(const int value) {
    if (m_first) return;
    DataManager::saveInfo("potassium", value);
}

void GoalsPage::cholesterolChanged(const int value) {
    if (m_first) return;
    DataManager::saveInfo("cholesterol", value);
}

void GoalsPage::goalChanged(int value) {
    if (m_first) return;
    if (recalcGoal()) DataManager::saveInfo("goal", value);
}

void GoalsPage::caloriesChanged(int value) {
    if (m_first) return;
    DataManager::saveInfo("calories", value);
}

void GoalsPage::weightChanged(double value) {
    if (m_first) return;
    DataManager::saveInfo("weight", value);
}

bool GoalsPage::recalcGoal()
{
    auto button = QMessageBox::question(this, "Recalculate Goals", "Are you sure you want to recalculate your goals? This will overwrite target calories, carbs, fats, and proteins.");
    if (button == QMessageBox::No) return false;

    int weightMultiplier = 0;
    int carbsPercentage = 30;
    int fatPercentage = 30;
    int proteinPercentage = 40;

    double weight = ui->weight->value();

    switch (ui->goal->currentIndex()) {
    // fast weight loss
    case 0:
        weightMultiplier = 15;
        fatPercentage = 25;
        proteinPercentage = 45;
        break;
    // slow weight loss
    case 1:
        weightMultiplier = 17;
        break;
    // maintain
    case 2:
        weightMultiplier = 18;
        break;
    // slow weight gain
    case 3:
        weightMultiplier = 19;
        carbsPercentage = 35;
        proteinPercentage = 35;
        break;
    // fast weight gain
    case 4:
        weightMultiplier = 21;
        carbsPercentage = 35;
        fatPercentage = 35;
        proteinPercentage = 30;
        break;
    default:
        break;
    }

    ui->calories->setValue(weight * weightMultiplier);
    ui->carbs->setValue(carbsPercentage);
    ui->fat->setValue(fatPercentage);
    ui->protein->setValue(proteinPercentage);

    return true;
}

bool GoalsPage::verifyMacros()
{
    int carbs = ui->carbs->value();
    int fat = ui->fat->value();
    int protein = ui->protein->value();

    bool good = carbs + fat + protein == 100;
    QPalette palette = ui->carbs->palette();
    palette.setColor(QPalette::Text, good ? Qt::white : Qt::red);

    ui->carbs->setPalette(palette);
    ui->fat->setPalette(palette);
    ui->protein->setPalette(palette);

    if (good) {
        DataManager::saveInfo("carbs", ui->carbs->value());
        DataManager::saveInfo("fat", ui->fat->value());
        DataManager::saveInfo("protein", ui->protein->value());
    }

    return good;
}
