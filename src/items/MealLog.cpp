#include "items/MealLog.h"
#include "data/CacheManager.h"
#include "dialogs/FoodServingEdit.h"
#include "ui_MealLog.h"

#include "dialogs/FoodSearch.h"

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

    connect(search, &FoodSearch::itemSelected, this, [this](const FoodItem &item, const ServingSize &size, const double units) {
        qDebug() << "caching";
        CacheManager::cacheFoodItem(item);
        qDebug() << "Cached";

        FoodInfoWidget *food = new FoodInfoWidget(item, this, size, units);

        connect(food, &FoodInfoWidget::selected, this, [this, food, item, size, units] {
            FoodServingEdit *edit = new FoodServingEdit(item, this, food->size(), food->units());
            edit->show();

            connect(edit, &FoodServingEdit::foodReady, this, [this, food](const FoodItem &item, const ServingSize &size, const double units) {
                food->setSize(size);
                food->setUnits(units);
                food->updateLabels();
            });
        });

        ui->verticalLayout->addWidget(food);
    });
}
