#ifndef GOALSPAGE_H
#define GOALSPAGE_H

#include <QWizardPage>

namespace Ui {
class GoalsPage;
}

class GoalsPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit GoalsPage(QWidget *parent = nullptr);
    ~GoalsPage();

private:
    Ui::GoalsPage *ui;
};

#endif // GOALSPAGE_H
