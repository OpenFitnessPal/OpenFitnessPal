#include "items/NutrientProgressBar.h"
#include "ui_NutrientProgressBar.h"

NutrientProgressBar::NutrientProgressBar(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::NutrientProgressBar)
{
    ui->setupUi(this);
}

NutrientProgressBar::~NutrientProgressBar()
{
    delete ui;
}

void NutrientProgressBar::setTarget(const double newTarget)
{
    m_target = newTarget;
    ui->target->setText(QString::number(newTarget) + m_unit);
    resetBar();
}

void NutrientProgressBar::setTotal(const double newTotal)
{
    m_total = newTotal;
    ui->total->setText(QString::number(newTotal) + m_unit);
    resetBar();
}

void NutrientProgressBar::setUnit(const QString &unit)
{
    m_unit = unit;
}

void NutrientProgressBar::resetBar()
{
    ui->bar->setValue(std::min(m_total / m_target * 100.0, 100.0));
}
