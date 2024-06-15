#ifndef FOODSEARCH_H
#define FOODSEARCH_H

#include <QDialog>
#include <OFP/OFPManager.h>
#include "items/FoodInfoWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class FoodSearch;
}
QT_END_NAMESPACE

class FoodSearch : public QDialog
{
    Q_OBJECT

public:
    FoodSearch(QWidget *parent = nullptr);
    ~FoodSearch();

public slots:
    void search();

signals:
    void itemSelected(const FoodItem &item, const ServingSize &size, const double units);

private:
    Ui::FoodSearch *ui;

    OFPManager *m_manager;
    QList<FoodInfoWidget *> m_widgets{};

    void addFood(FoodItem &item);
};
#endif // FOODSEARCH_H
