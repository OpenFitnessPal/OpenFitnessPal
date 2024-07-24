#include "pages/SettingsPage.h"
#include "ui_SettingsPage.h"
#include "Settings.h"

#include <QScroller>

SettingsPage::SettingsPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SettingsPage)
{
    ui->setupUi(this);

    QScroller::grabGesture(ui->scrollArea, QScroller::LeftMouseButtonGesture);

    ui->meal1->setText(Settings::Meal1Name.value().toString());
    ui->meal2->setText(Settings::Meal2Name.value().toString());
    ui->meal3->setText(Settings::Meal3Name.value().toString());
    ui->meal4->setText(Settings::Meal4Name.value().toString());
    ui->meal5->setText(Settings::Meal5Name.value().toString());
}

SettingsPage::~SettingsPage()
{
    delete ui;
}

void SettingsPage::meal1Changed()
{
    Settings::Meal1Name.setValue(ui->meal1->text());
}

void SettingsPage::meal2Changed()
{
    Settings::Meal2Name.setValue(ui->meal2->text());
}

void SettingsPage::meal3Changed()
{
    Settings::Meal3Name.setValue(ui->meal3->text());
}

void SettingsPage::meal4Changed()
{
    Settings::Meal4Name.setValue(ui->meal4->text());
}

void SettingsPage::meal5Changed()
{
    Settings::Meal5Name.setValue(ui->meal5->text());
}
