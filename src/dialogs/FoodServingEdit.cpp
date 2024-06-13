#include "dialogs/FoodServingEdit.h"
#include "ui_FoodServingEdit.h"

// TODO: Configurable based on selected size
FoodServingEdit::FoodServingEdit(const FoodItem &item, QWidget *parent, const ServingSize &size, const double units)
    : QDialog(parent)
    , ui(new Ui::FoodServingEdit)
    , m_item(item)
{
    ui->setupUi(this);

    ui->food->setText(item.name());

    for (const ServingSize &servingSize : item.servingSizes()) {
        if (!m_sizeMap.contains(servingSize.unit())) {
            ui->size->addItem(servingSize.unit());
            m_sizeMap.insert(servingSize.unit(), servingSize);
        }

        if (size.baseMultiplier() != 0.0) {
            ui->size->setCurrentText(size.unit());
            ui->servings->setValue(units);
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

    ui->carbs->setText(QString::number(m_item.carbs() * mult) + "g");
    ui->fat->setText(QString::number(m_item.fat() * mult) + "g");
    ui->protein->setText(QString::number(m_item.protein() * mult) + "g");
    ui->calories->setText(QString::number(m_item.calories() * mult));
}

void FoodServingEdit::sendFood() {
    emit foodReady(m_item, m_sizeMap.value(ui->size->currentText()), ui->servings->value());
    accept();
}
