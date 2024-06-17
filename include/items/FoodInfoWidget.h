#ifndef SEARCHITEMWIDGET_H
#define SEARCHITEMWIDGET_H

#include <OFP/FoodItem.h>
#include <QWidget>

namespace Ui {
class FoodInfoWidget;
}

class FoodInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FoodInfoWidget(const FoodItem &item, QWidget *parent = nullptr, const ServingSize &size = ServingSize{}, const double units = 1);
    ~FoodInfoWidget();

    FoodItem item();

    ServingSize size() const;
    void setSize(const ServingSize &newSize);

    double units() const;
    void setUnits(double newUnits);

    void updateLabels();

    void showDelete();

public slots:
    void remove();

private:
    Ui::FoodInfoWidget *ui;

    FoodItem m_item;
    ServingSize m_size;
    double m_units;

    void mousePressEvent(QMouseEvent *e);

signals:
    void selected();
    void deleteRequested();
};

#endif // SEARCHITEMWIDGET_H
