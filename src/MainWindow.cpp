#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->dateEdit->setDate(QDate::currentDate());

    connect(ui->dateEdit, &QDateEdit::userDateChanged, ui->food, &JournalPage::setDate);
    connect(ui->dateEdit, &QDateEdit::userDateChanged, ui->exercise, &ExercisePage::setDate);

    connect(ui->tabWidget, &QTabWidget::currentChanged, this, [this](int i) {
        if (i == ui->tabWidget->indexOf(ui->food)) {
            ui->food->updateMealNames();
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
