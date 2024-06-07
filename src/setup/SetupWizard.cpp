#include "setup/SetupWizard.h"
#include "ui_SetupWizard.h"

SetupWizard::SetupWizard(QWidget *parent)
    : QWizard(parent)
    , ui(new Ui::SetupWizard)
{
    ui->setupUi(this);
}

SetupWizard::~SetupWizard()
{
    delete ui;
}
