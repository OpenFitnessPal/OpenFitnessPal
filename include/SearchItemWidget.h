#ifndef SEARCHITEMWIDGET_H
#define SEARCHITEMWIDGET_H

#include <OFP/FoodItem.h>
#include <QWidget>

namespace Ui {
class SearchItemWidget;
}

class SearchItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SearchItemWidget(const FoodItem &item, QWidget *parent = nullptr);
    ~SearchItemWidget();

    FoodItem item();

private:
    Ui::SearchItemWidget *ui;

    FoodItem m_item;

    void mousePressEvent(QMouseEvent *e);

    const QString m_siteName;

signals:
    void selected();
};

#endif // SEARCHITEMWIDGET_H
