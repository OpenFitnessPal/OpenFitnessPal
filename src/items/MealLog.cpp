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

        connect(edit, &FoodServingEdit::foodReady, this, [this, food](const FoodItem &item, const ServingSize &servingSize, const double units) {
            food->setSize(servingSize);
            food->setUnits(units);
            food->updateLabels();

            emit foodsChanged();

            DataManager::saveFood(m_number, m_date, item, servingSize, units);
        });
    });

    connect(food, &FoodInfoWidget::deleteRequested, this, [this, food, item] {
        DataManager::removeFood(m_number, m_date, item);
        ui->verticalLayout->removeWidget(food);
        m_widgets.removeOne(food);
        food->deleteLater();

        emit foodsChanged();
    });

    emit foodsChanged();

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

NutrientUnion MealLog::getNutrients()
{
    NutrientUnion n;
    for (FoodInfoWidget *w : m_widgets) {
        FoodItem item = w->item();

        double mult = w->size().baseMultiplier() * w->units();

        n.calcium += item.calcium() * mult;
        n.carbs += item.carbs() * mult;
        n.fat += item.fat() * mult;
        n.satFat += item.satFat() * mult;
        n.monoFat += item.monoFat() * mult;
        n.polyFat += item.polyFat() * mult;
        n.transFat += item.transFat() * mult;
        n.fiber += item.fiber() * mult;
        n.sugar += item.sugar() * mult;
        n.addedSugar += item.addedSugar() * mult;
        n.protein += item.protein() * mult;
        n.cholesterol += item.cholesterol() * mult;
        n.iron += item.iron() * mult;
        n.sodium += item.sodium() * mult;
        n.potassium += item.potassium() * mult;
        n.vitaminA += item.vitaminA() * mult;
        n.vitaminC += item.vitaminC() * mult;
        n.vitaminD += item.vitaminD() * mult;
    }

    return n;
}
