#include "SearchItemWidget.h"
#include "ui_SearchItemWidget.h"

#include <QDesktopServices>

// TODO: make this more extensible and usable
SearchItemWidget::SearchItemWidget(const FoodItem &item, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SearchItemWidget)
    , m_siteName(item.siteName())
{
    ui->setupUi(this);

    m_item = item;

    ServingSize size;

    for (ServingSize serving : item.servingSizes()) {
        if (serving.baseMultiplier() == 1) {
            size = serving;
        }
    }

    ui->brand->setText(item.brand() + ", " + QString::number(size.defaultValue()) + " " + size.unit());
    ui->cals->setText(QString::number(item.calories()));
    ui->food->setText(item.name());
}

SearchItemWidget::~SearchItemWidget()
{
    delete ui;
}

void SearchItemWidget::mousePressEvent(QMouseEvent *e) {
    // QUrl url("https://www.myfitnesspal.com/food/nutrition-calories/" + m_siteName);
    // QDesktopServices::openUrl(url);
    emit selected();
}

FoodItem SearchItemWidget::item() {
    return m_item;
}
