#ifndef JOURNALITEM_H
#define JOURNALITEM_H

#include <QWidget>

namespace Ui {
class JournalItem;
}

class JournalItem : public QWidget
{
    Q_OBJECT

public:
    explicit JournalItem(QWidget *parent = nullptr);
    ~JournalItem();

private:
    Ui::JournalItem *ui;
};

#endif // JOURNALITEM_H
