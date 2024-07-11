#include "dialogs/FoodSearch.h"
#include "data/DataManager.h"
#include "dialogs/FoodServingEdit.h"
#include "dialogs/RecipeAdd.h"
#include "items/FoodInfoWidget.h"
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
    connect(this, &QDialog::finished, m_manager, &OFPManager::cancelAll);
}

FoodSearch::~FoodSearch()
{
    delete ui;
}

void FoodSearch::search()
{
    QLayout *layout = ui->tabWidget->currentWidget()->layout();
    for (QWidget *w : m_widgets.values(layout)) {
        layout->removeWidget(w);
        w->setHidden(true);
    }

    m_widgets.remove(layout);

    switch (ui->tabWidget->currentIndex()) {
    // online
    case 0:
        ui->submit->setDisabled(true);
        m_manager->search(ui->searchBar->text());
        m_manager->connect(m_manager, &OFPManager::searchComplete, this, [this](QList<FoodItem> items) {
            for (const FoodItem &item : items) {
                addFood(item, ui->onlineWidgets);
            }
            ui->submit->setEnabled(true);
        }, Qt::SingleShotConnection);
        break;
    // offline
    case 1:
        for (const FoodItem &item : CacheManager::search(ui->searchBar->text())) {
            addFood(item, ui->offlineWidgets);
        }
        break;
    // recipes
    case 2: {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        QRegExp regex(".*" + ui->searchBar->text() + ".*", Qt::CaseInsensitive);
#else
        QRegularExpression regex(".*" + ui->searchBar->text() + ".*", QRegularExpression::PatternOption::CaseInsensitiveOption);
#endif

        for (const Recipe &recipe : DataManager::loadRecipes()) {
            if (recipe.name().contains(regex)) {
                addRecipe(recipe);
            }
        }
        break;
    }
    default:
        break;
    }
}

void FoodSearch::addFood(const FoodItem &item, QVBoxLayout *layout)
{
    FoodInfoWidget *widget = new FoodInfoWidget(FoodServing{item}, this);

    connect(widget, &FoodInfoWidget::selected, this, [this, item]() mutable {
        FoodServingEdit *m_edit = new FoodServingEdit(FoodServing{item}, this);
        m_edit->show();

        connect(m_edit, &FoodServingEdit::foodReady, this, &FoodSearch::itemSelected);
        connect(m_edit, &FoodServingEdit::foodReady, this, &FoodSearch::close);
    });

    layout->addWidget(widget, 1, Qt::AlignTop);
    widget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_widgets.insert(layout, widget);
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

    ui->recipeWidgets->addWidget(widget, 1, Qt::AlignTop);
    widget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_widgets.insert(ui->recipeWidgets, widget);

}
