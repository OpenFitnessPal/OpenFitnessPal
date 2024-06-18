#include "pages/JournalPage.h"
#include "Settings.h"
#include "ui_JournalPage.h"

JournalPage::JournalPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::JournalPage)
{
    ui->setupUi(this);

    updateMealNames();

    ui->meal1->setNumber(1);
    ui->meal2->setNumber(2);
    ui->meal3->setNumber(3);
    ui->meal4->setNumber(4);
    ui->meal5->setNumber(5);

    connect(ui->meal1, &MealLog::foodsChanged, this, &JournalPage::updateMacroPreview);
    connect(ui->meal2, &MealLog::foodsChanged, this, &JournalPage::updateMacroPreview);
    connect(ui->meal3, &MealLog::foodsChanged, this, &JournalPage::updateMacroPreview);
    connect(ui->meal4, &MealLog::foodsChanged, this, &JournalPage::updateMacroPreview);
    connect(ui->meal5, &MealLog::foodsChanged, this, &JournalPage::updateMacroPreview);

    updateMacroPreview();
}

JournalPage::~JournalPage()
{
    delete ui;
}

NutrientUnion JournalPage::getNutrients()
{
    NutrientUnion n;
    n += ui->meal1->getNutrients();
    n += ui->meal2->getNutrients();
    n += ui->meal3->getNutrients();
    n += ui->meal4->getNutrients();
    n += ui->meal5->getNutrients();
    return n;
}

void JournalPage::setDate(QDate date)
{
    ui->meal1->setDate(date);
    ui->meal2->setDate(date);
    ui->meal3->setDate(date);
    ui->meal4->setDate(date);
    ui->meal5->setDate(date);
}

void JournalPage::updateMealNames()
{
    ui->meal1->setMealName(Settings::Meal1Name.value().toString());
    ui->meal2->setMealName(Settings::Meal2Name.value().toString());
    ui->meal3->setMealName(Settings::Meal3Name.value().toString());
    ui->meal4->setMealName(Settings::Meal4Name.value().toString());
    ui->meal5->setMealName(Settings::Meal5Name.value().toString());
}

void JournalPage::updateMacroPreview()
{
    ui->macros->setNutrients(getNutrients());
}
