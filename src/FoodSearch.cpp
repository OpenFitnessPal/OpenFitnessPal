#include "FoodSearch.h"
#include "ui_FoodSearch.h"

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
    for (SearchItemWidget *w : m_widgets) {
        ui->results->removeWidget(w);
        w->deleteLater();
    }

    m_manager->search(ui->searchBar->text());
    m_manager->connect(m_manager, &OFPManager::searchComplete, this, [this](QList<FoodItem> items) {
        for (FoodItem &item : items) {
            SearchItemWidget *widget = new SearchItemWidget(item, this);

            connect(widget, &SearchItemWidget::selected, this, [this, item]() mutable {
                emit itemSelected(item);
                close();
            });

            ui->results->addWidget(widget);
            m_widgets.append(widget);
        }
    });
}
