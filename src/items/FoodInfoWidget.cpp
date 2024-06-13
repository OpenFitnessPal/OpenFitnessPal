#include "items/FoodInfoWidget.h"
#include "ui_FoodInfoWidget.h"

#include <QDesktopServices>

// TODO: make this more extensible and usable
FoodInfoWidget::FoodInfoWidget(const FoodItem &item, QWidget *parent, const ServingSize &size, const double units)
    : QWidget(parent)
    , ui(new Ui::FoodInfoWidget)
    , m_item(item)
    , m_units(units)
{
    ui->setupUi(this);

    ServingSize servingSize = size;

    if (size.baseMultiplier() == 0.0) {
        for (ServingSize serving : item.servingSizes()) {
            if (serving.baseMultiplier() == 1) {
                servingSize = serving;
            }
        }
    }

    m_size = servingSize;
    updateLabels();
}

FoodInfoWidget::~FoodInfoWidget()
{
    delete ui;
}

void FoodInfoWidget::updateLabels() {
    ui->brand->setText(m_item.brand() + ", " + QString::number(m_units * m_size.defaultValue()) + " " + m_size.baseUnit());
    ui->cals->setText(QString::number(m_item.calories() * m_size.multiplier(m_units)) + "kcal");
    ui->food->setText(m_item.name());
}

void FoodInfoWidget::mousePressEvent(QMouseEvent *e) {
    emit selected();
}

FoodItem FoodInfoWidget::item() {
    return m_item;
}

ServingSize FoodInfoWidget::size() const
{
    return m_size;
}

void FoodInfoWidget::setSize(const ServingSize &newSize)
{
    m_size = newSize;
}

double FoodInfoWidget::units() const
{
    return m_units;
}

void FoodInfoWidget::setUnits(double newUnits)
{
    m_units = newUnits;
}