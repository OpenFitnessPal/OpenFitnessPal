#include "items/FoodInfoWidget.h"
#include "ui_FoodInfoWidget.h"

#include <QDesktopServices>
#include <QMouseEvent>

// TODO: improve touch control
FoodInfoWidget::FoodInfoWidget(const FoodServing &food, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FoodInfoWidget)
    , m_food(food)
{
    ui->setupUi(this);
    ui->remove->setHidden(true);

    if (m_food.size.baseMultiplier() == 0.0) {
        m_food.size = food.item.defaultServing();
        m_food.units = 1.0;
    }

    updateLabels();
}

FoodInfoWidget::~FoodInfoWidget()
{
    delete ui;
}

void FoodInfoWidget::updateLabels() {
    ui->brand->setText(m_food.item.brand() + ", " + QString::number(m_food.units * m_food.size.defaultValue()) + " " + m_food.size.baseUnit());
    ui->cals->setText(QString::number(m_food.item.nutrients().calories() * m_food.size.multiplier(m_food.units)) + "kcal");
    ui->food->setText(m_food.item.name());
}

void FoodInfoWidget::showDelete()
{
    ui->remove->setHidden(false);
}

void FoodInfoWidget::remove()
{
    emit deleteRequested();
}

FoodServing FoodInfoWidget::food() const
{
    return m_food;
}

void FoodInfoWidget::setFood(const FoodServing &newServing)
{
    m_food = newServing;
    updateLabels();
}

void FoodInfoWidget::mouseReleaseEvent(QMouseEvent *e) {
    emit selected();
}
