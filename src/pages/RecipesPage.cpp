#include "pages/RecipesPage.h"
#include "ui_RecipesPage.h"

#include <items/RecipeInfoWidget.h>

#include <dialogs/RecipeEdit.h>

#include <data/DataManager.h>

RecipesPage::RecipesPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RecipesPage)
{
    ui->setupUi(this);

    QList<Recipe> recipes = DataManager::loadRecipes();

    for (const Recipe &recipe : recipes) {
        addRecipe(recipe);
    }
}

void RecipesPage::addItem() {
    RecipeEdit *edit = new RecipeEdit(this);
    edit->show();

    connect(edit, &RecipeEdit::recipeReady, this, [this](const Recipe &recipe) {
        DataManager::saveRecipe(recipe);

        addRecipe(recipe);
    });
}

void RecipesPage::addRecipe(const Recipe &recipe)
{
    RecipeInfoWidget *recipeWidget = new RecipeInfoWidget(recipe, 1, this);
    recipeWidget->showDelete();

    m_widgets.append(recipeWidget);

    connect(recipeWidget, &RecipeInfoWidget::selected, this, [this, recipeWidget] {
        RecipeEdit *edit = new RecipeEdit(this, recipeWidget->recipe(), recipeWidget->units());
        edit->show();

        connect(edit, &RecipeEdit::recipeReady, this, [this, recipeWidget](const Recipe &newRecipe) {
            DataManager::removeRecipe(recipeWidget->recipe());

            recipeWidget->setRecipe(newRecipe);
            recipeWidget->updateLabels();

            DataManager::saveRecipe(newRecipe);
        });
    });

    connect(recipeWidget, &RecipeInfoWidget::deleteRequested, this, [this, recipeWidget] {
        DataManager::removeRecipe(recipeWidget->recipe());

        ui->verticalLayout->removeWidget(recipeWidget);
        m_widgets.removeOne(recipeWidget);
        recipeWidget->deleteLater();
    });

    ui->recipes->addWidget(recipeWidget, 1, Qt::AlignTop);
    recipeWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
}


RecipesPage::~RecipesPage()
{
    delete ui;
}
