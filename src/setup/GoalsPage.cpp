#include "setup/GoalsPage.h"
#include "ui_GoalsPage.h"

GoalsPage::GoalsPage(QWidget *parent)
    : QWizardPage(parent)
    , ui(new Ui::GoalsPage)
{
    ui->setupUi(this);
}

GoalsPage::~GoalsPage()
{
    delete ui;
}
