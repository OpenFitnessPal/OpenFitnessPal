#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <OFP/OFPManager.h>
#include "SearchItemWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void search();
private:
    Ui::MainWindow *ui;

    OFPManager *m_manager;
    QList<SearchItemWidget *> m_widgets{};
};
#endif // MAINWINDOW_H
