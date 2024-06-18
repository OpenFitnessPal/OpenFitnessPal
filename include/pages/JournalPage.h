#ifndef JOURNALPAGE_H
#define JOURNALPAGE_H

#include "NutrientUnion.h"
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

    NutrientUnion getNutrients();

public slots:
    void setDate(QDate date);
    void updateMealNames();

    void updateMacroPreview();

private:
    Ui::JournalPage *ui;
};

#endif // JOURNALPAGE_H
