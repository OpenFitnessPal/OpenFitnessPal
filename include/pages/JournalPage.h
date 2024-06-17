#ifndef JOURNALPAGE_H
#define JOURNALPAGE_H

#include <QWidget>

namespace Ui {
class JournalPage;
}

class JournalPage : public QWidget
{
    Q_OBJECT

public:
    explicit JournalPage(QWidget *parent = nullptr);
    ~JournalPage();

public slots:
    void setDate(QDate date);

private:
    Ui::JournalPage *ui;
};

#endif // JOURNALPAGE_H
