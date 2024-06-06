#include "MainWindow.h"
#include "ui/ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_manager = new OFPManager(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::search()
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
