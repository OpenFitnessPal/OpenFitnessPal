#include "dialogs/FoodSearch.h"
#include "data/DataManager.h"
#include "dialogs/FoodServingEdit.h"
#include "dialogs/RecipeAdd.h"
#include "items/RecipeInfoWidget.h"
#include "ui_FoodSearch.h"

#include <data/CacheManager.h>

// TODO: change this to use tabs
FoodSearch::FoodSearch(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FoodSearch)
{
    ui->setupUi(this);

    m_manager = new OFPManager(this);
}

FoodSearch::~FoodSearch()
{
    delete ui;
}

void FoodSearch::search()
{
    for (QWidget *w : m_widgets) {
        ui->results->removeWidget(w);
        w->setHidden(true);
    }

    if (ui->offline->isChecked()) {
        if (ui->recipes->isChecked()) {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
            QRegExp regex(".*" + ui->searchBar->text() + ".*", Qt::CaseInsensitive);
#else
            QRegularExpression regex(".*" + ui->searchBar->text() + ".*", QRegularExpression::PatternOption::CaseInsensitiveOption);
#endif

            QList<Recipe> allRecipes = DataManager::loadRecipes();

            for (const Recipe &recipe : allRecipes) {
                if (recipe.name().contains(regex)) {
                    addRecipe(recipe);
                }
            }
        } else {
            QList<FoodItem> foods = CacheManager::search(ui->searchBar->text());
            for (const FoodItem &item : foods) {
                addFood(item);
            }
        }
    } else {
        m_manager->search(ui->searchBar->text());
        m_manager->connect(m_manager, &OFPManager::searchComplete, this, [this](QList<FoodItem> items) {
                for (const FoodItem &item : items) {
                    addFood(item);
                }
            }, Qt::SingleShotConnection);
    }
}

void FoodSearch::addFood(const FoodItem &item)
{
    FoodInfoWidget *widget = new FoodInfoWidget(FoodServing{item}, this);

    connect(widget, &FoodInfoWidget::selected, this, [this, item]() mutable {
        FoodServingEdit *m_edit = new FoodServingEdit(FoodServing{item}, this);
        m_edit->show();

        connect(m_edit, &FoodServingEdit::foodReady, this, &FoodSearch::itemSelected);
        connect(m_edit, &FoodServingEdit::foodReady, this, &FoodSearch::close);
    });

    ui->results->addWidget(widget);
    m_widgets.append(widget);
}

void FoodSearch::addRecipe(const Recipe &recipe)
{
    RecipeInfoWidget *widget = new RecipeInfoWidget(recipe, 1, this);

    connect(widget, &RecipeInfoWidget::selected, this, [this, recipe]() mutable {
        RecipeAdd *edit = new RecipeAdd(this, recipe);
        edit->show();

        connect(edit, &RecipeAdd::recipeReady, this, &FoodSearch::recipeSelected);
        connect(edit, &RecipeAdd::recipeReady, this, &FoodSearch::close);
    });

    ui->results->addWidget(widget);
    m_widgets.append(widget);

}
