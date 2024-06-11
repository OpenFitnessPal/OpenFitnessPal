#include "items/JournalItem.h"
#include "ui_JournalItem.h"

JournalItem::JournalItem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::JournalItem)
{
    ui->setupUi(this);
}

JournalItem::~JournalItem()
{
    delete ui;
}
