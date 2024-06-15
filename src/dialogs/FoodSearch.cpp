#include "dialogs/FoodSearch.h"
#include "dialogs/FoodServingEdit.h"
#include "ui_FoodSearch.h"

#include <data/CacheManager.h>



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
    for (FoodInfoWidget *w : m_widgets) {
        ui->results->removeWidget(w);
        w->deleteLater();
    }

    if (ui->offline->isChecked()) {
        QList<FoodItem> foods = CacheManager::search(ui->searchBar->text());
        for (FoodItem &item : foods) {
            addFood(item);
        }
    } else {
        m_manager->search(ui->searchBar->text());
        m_manager->connect(m_manager, &OFPManager::searchComplete, this, [this](QList<FoodItem> items) {
                for (FoodItem &item : items) {
                    addFood(item);
                }
            }, Qt::SingleShotConnection);
    }
}

void FoodSearch::addFood(FoodItem &item)
{
    FoodInfoWidget *widget = new FoodInfoWidget(item, this);

    connect(widget, &FoodInfoWidget::selected, this, [this, item]() mutable {
        FoodServingEdit *m_edit = new FoodServingEdit(item, this);
        m_edit->show();

        connect(m_edit, &FoodServingEdit::foodReady, this, &FoodSearch::itemSelected);
        connect(m_edit, &FoodServingEdit::foodReady, this, &FoodSearch::close);
    });

    ui->results->addWidget(widget);
    m_widgets.append(widget);
}
