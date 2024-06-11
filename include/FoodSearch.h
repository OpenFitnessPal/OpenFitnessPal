#ifndef FOODSEARCH_H
#define FOODSEARCH_H

#include <QDialog>
#include <OFP/OFPManager.h>
#include "SearchItemWidget.h"

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
    void itemSelected(FoodItem &item);

private:
    Ui::FoodSearch *ui;

    OFPManager *m_manager;
    QList<SearchItemWidget *> m_widgets{};
};
#endif // FOODSEARCH_H
