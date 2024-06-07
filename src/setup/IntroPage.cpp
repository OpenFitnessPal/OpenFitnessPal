#include "setup/IntroPage.h"
#include "ui_IntroPage.h"

IntroPage::IntroPage(QWidget *parent)
    : QWizardPage(parent)
    , ui(new Ui::IntroPage)
{
    ui->setupUi(this);
}

IntroPage::~IntroPage()
{
    delete ui;
}
