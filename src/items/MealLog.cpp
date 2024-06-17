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
    m_date = QDate::currentDate();
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
        CacheManager::cacheFoodItem(item);
        DataManager::saveFood(m_number, QDate::currentDate(), item, size, units);

        addFood(item, size, units);
    });
}

void MealLog::addFood(const FoodItem &item, const ServingSize &size, const double units)
{
    FoodInfoWidget *food = new FoodInfoWidget(item, this, size, units);
    food->showDelete();
    m_widgets.append(food);

    connect(food, &FoodInfoWidget::selected, this, [this, food, item, size, units] {
        FoodServingEdit *edit = new FoodServingEdit(item, this, food->size(), food->units());
        edit->show();

        connect(edit, &FoodServingEdit::foodReady, this, [this, food](const FoodItem &item, const ServingSize &size, const double units) {
            food->setSize(size);
            food->setUnits(units);
            food->updateLabels();

            DataManager::saveFood(m_number, m_date, item, size, units);
        });
    });

    connect(food, &FoodInfoWidget::deleteRequested, this, [this, food, item] {
        DataManager::removeFood(m_number, m_date, item);
        ui->verticalLayout->removeWidget(food);
        m_widgets.removeOne(food);
        food->deleteLater();
    });

    ui->verticalLayout->addWidget(food);

}

void MealLog::addFood(const FoodServing &serving)
{
    addFood(std::get<0>(serving),
            std::get<1>(serving),
            std::get<2>(serving));
}

void MealLog::reloadFood()
{
    QList<FoodServing> foods = DataManager::loadFoods(m_number, m_date);

    for (const FoodServing &serving : foods) {
        addFood(serving);
    }
}

void MealLog::setDate(QDate date)
{
    if (date != m_date) {
        for (QWidget *w : m_widgets) {
            ui->verticalLayout->removeWidget(w);
            w->deleteLater();
            m_widgets.removeOne(w);
        }

        m_date = date;
        reloadFood();
    }
    else m_date = date;
}

void MealLog::setNumber(int newNumber)
{
    m_number = newNumber;

    reloadFood();
}
