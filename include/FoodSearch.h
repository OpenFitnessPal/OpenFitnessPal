#ifndef FOODSEARCH_H
#define FOODSEARCH_H

#include <QMainWindow>
#include <OFP/OFPManager.h>
#include "SearchItemWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class FoodSearch;
}
QT_END_NAMESPACE

class FoodSearch : public QWidget
{
    Q_OBJECT

public:
    FoodSearch(QWidget *parent = nullptr);
    ~FoodSearch();

public slots:
    void search();
private:
    Ui::FoodSearch *ui;

    OFPManager *m_manager;
    QList<SearchItemWidget *> m_widgets{};
};
#endif // FOODSEARCH_H
