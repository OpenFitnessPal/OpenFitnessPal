#include "items/MealLog.h"
#include "data/CacheManager.h"
#include "dialogs/FoodServingEdit.h"
#include "items/FoodInfoWidget.h"
#include "ui_MealLog.h"

#include "dialogs/FoodSearch.h"

#include <data/DataManager.h>

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

    connect(search, &FoodSearch::itemSelected, this, [this](const FoodServing &food) {
        CacheManager::cacheFoodItem(food.item);
        DataManager::saveFood(m_number, QDate::currentDate(), food);

        addFood(food);
    });

    connect(search, &FoodSearch::recipeSelected, this, [this](const Recipe &recipe, const double units) {
        for (FoodServing food : recipe.foods()) {
            food.units *= units / recipe.servings();

            CacheManager::cacheFoodItem(food.item);
            DataManager::saveFood(m_number, QDate::currentDate(), food);

            addFood(food);
        }
    });
}

void MealLog::addFood(const FoodServing &serving)
{
    FoodInfoWidget *food = new FoodInfoWidget(serving, this);
    food->showDelete();
    m_widgets.append(food);

    connect(food, &FoodInfoWidget::selected, this, [this, food] {
        FoodServingEdit *edit = new FoodServingEdit(food->food(), this);
        edit->show();

        connect(edit, &FoodServingEdit::foodReady, this, [this, food](const FoodServing &serving) {
            DataManager::removeFood(m_number, m_date, food->food());

            food->setFood(serving);
            food->updateLabels();

            emit foodsChanged();

            DataManager::saveFood(m_number, m_date, serving);
        });
    });

    connect(food, &FoodInfoWidget::deleteRequested, this, [this, food, serving] {
        DataManager::removeFood(m_number, m_date, serving);
        ui->verticalLayout->removeWidget(food);
        m_widgets.removeOne(food);
        food->deleteLater();

        emit foodsChanged();
    });

    emit foodsChanged();

    ui->verticalLayout->addWidget(food);

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

NutrientUnion MealLog::getNutrients()
{
    NutrientUnion n;
    for (FoodInfoWidget *w : m_widgets) {
        FoodItem item = w->food().item;

        double mult = w->food().size.baseMultiplier() * w->food().units;

        n += item.nutrients() * mult;
    }

    return n;
}
