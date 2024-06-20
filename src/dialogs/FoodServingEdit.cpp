#include "dialogs/FoodServingEdit.h"
#include "ui_FoodServingEdit.h"

FoodServingEdit::FoodServingEdit(const FoodServing &food, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FoodServingEdit)
    , m_item(food.item)
{
    ui->setupUi(this);

    ui->food->setText(m_item.name());

    for (const ServingSize &servingSize : m_item.servingSizes()) {
        if (!m_sizeMap.contains(servingSize.unit())) {
            ui->size->addItem(servingSize.unit());
            m_sizeMap.insert(servingSize.unit(), servingSize);
        }

        if (food.size.baseMultiplier() != 0.0) {
            ui->size->setCurrentText(food.size.unit());
            ui->servings->setValue(food.units);
        }
        else if (servingSize.baseMultiplier() == 1.0) {
            ui->size->setCurrentText(servingSize.unit());
        }
    }

    calcMacros();
}

FoodServingEdit::~FoodServingEdit()
{
    delete ui;
}

void FoodServingEdit::calcMacros() {
    const ServingSize size = m_sizeMap.value(ui->size->currentText());

    if (size.baseMultiplier() == 0.0) return;

    const double mult = size.multiplier(ui->servings->value());

    NutrientUnion n = m_item.nutrients();

    ui->carbs->setText(QString::number(n.carbs * mult) + "g");
    ui->fat->setText(QString::number(n.fat * mult) + "g");
    ui->protein->setText(QString::number(n.protein * mult) + "g");
    ui->calories->setText(QString::number(n.calories() * mult));
}

void FoodServingEdit::sendFood() {
    emit foodReady(FoodServing{m_item, m_sizeMap.value(ui->size->currentText()), ui->servings->value()});
    accept();
}
