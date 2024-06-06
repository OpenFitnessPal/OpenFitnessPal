#include "SearchItemWidget.h"
#include "ui_SearchItemWidget.h"

#include <QDesktopServices>

SearchItemWidget::SearchItemWidget(const FoodItem &item, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SearchItemWidget)
    , m_siteName(item.siteName())
{
    ui->setupUi(this);

    ui->food->setText(item.name());
    ui->brand->setText(item.brand());
    ui->cals->setText(QString::number(item.calories()) + " kcal");
}

SearchItemWidget::~SearchItemWidget()
{
    delete ui;
}

void SearchItemWidget::mousePressEvent(QMouseEvent *e) {
    QUrl url("https://www.myfitnesspal.com/food/nutrition-calories/" + m_siteName);
    QDesktopServices::openUrl(url);
}
