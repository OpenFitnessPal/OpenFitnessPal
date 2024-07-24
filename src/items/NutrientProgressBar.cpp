#include "items/NutrientProgressBar.h"
#include "ui_NutrientProgressBar.h"

NutrientProgressBar::NutrientProgressBar(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::NutrientProgressBar)
{
    ui->setupUi(this);
    ui->bar->setValue(0);
}

NutrientProgressBar::~NutrientProgressBar()
{
    delete ui;
}

void NutrientProgressBar::setTarget(const double newTarget)
{
    m_target = newTarget;
    reset();
}

void NutrientProgressBar::setTotal(const double newTotal)
{
    m_total = newTotal;
    reset();
}

void NutrientProgressBar::setUnit(const QString &unit)
{
    m_unit = unit;
    reset();
}

void NutrientProgressBar::setName(const QString &name)
{
    m_name = name;
    reset();
}

void NutrientProgressBar::reset()
{
    ui->bar->setValue(std::min(m_total / m_target * 100.0, 100.0));
    ui->target->setText(QString::number(std::round(m_target * 100.) / 100.) + m_unit);
    ui->total->setText(QString::number(std::round(m_total * 100.) / 100.) + m_unit);

    double left = std::round((m_target - m_total) * 100.) / 100.;
    if (left < 0) left = 0;
    ui->left->setText(QString::number(left) + m_unit);
    ui->name->setText(m_name);
}
