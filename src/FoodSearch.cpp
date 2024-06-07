#include "FoodSearch.h"
#include "ui_FoodSearch.h"

FoodSearch::FoodSearch(QWidget *parent)
    : QWidget(parent)
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
    for (SearchItemWidget *w : m_widgets) {
        ui->results->removeWidget(w);
        w->deleteLater();
    }

    m_manager->search(ui->searchBar->text());
    m_manager->connect(m_manager, &OFPManager::searchComplete, this, [this](QList<FoodItem> items) {
        for (const FoodItem &item : items) {
            SearchItemWidget *widget = new SearchItemWidget(item, this);
            ui->results->addWidget(widget);
            m_widgets.append(widget);
        }
    });
}
