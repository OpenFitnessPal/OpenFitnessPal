#include "items/MealLog.h"
#include "ui_MealLog.h"

#include "FoodSearch.h"

MealLog::MealLog(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MealLog)
{
    ui->setupUi(this);
}

MealLog::~MealLog()
{
    delete ui;
}

void MealLog::setMealName(const QString &name) {
    ui->label->setText(name);
}

void MealLog::addItem() {
    FoodSearch *search = new FoodSearch(this);
    search->show();

    connect(search, &FoodSearch::itemSelected, this, [this](FoodItem &item) {
        SearchItemWidget *widget = new SearchItemWidget(item, this);

        ui->verticalLayout->addWidget(widget);
    });
}
