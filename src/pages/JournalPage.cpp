#include "pages/JournalPage.h"
#include "ui_JournalPage.h"

JournalPage::JournalPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::JournalPage)
{
    ui->setupUi(this);

    ui->meal1->setMealName("Meal 1");
    ui->meal2->setMealName("Meal 2");
    ui->meal3->setMealName("Meal 3");
    ui->meal4->setMealName("Meal 4");
    ui->meal5->setMealName("Meal 5");
}

JournalPage::~JournalPage()
{
    delete ui;
}
