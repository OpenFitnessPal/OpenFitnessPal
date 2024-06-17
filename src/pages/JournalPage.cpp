#include "pages/JournalPage.h"
#include "ui_JournalPage.h"

JournalPage::JournalPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::JournalPage)
{
    ui->setupUi(this);

    ui->meal1->setMealName("Meal 1");
    ui->meal1->setNumber(1);
    ui->meal2->setMealName("Meal 2");
    ui->meal2->setNumber(2);
    ui->meal3->setMealName("Meal 3");
    ui->meal3->setNumber(3);
    ui->meal4->setMealName("Meal 4");
    ui->meal4->setNumber(4);
    ui->meal5->setMealName("Meal 5");
    ui->meal5->setNumber(5);
}

JournalPage::~JournalPage()
{
    delete ui;
}

void JournalPage::setDate(QDate date)
{
    ui->meal1->setDate(date);
    ui->meal2->setDate(date);
    ui->meal3->setDate(date);
    ui->meal4->setDate(date);
    ui->meal5->setDate(date);
}
