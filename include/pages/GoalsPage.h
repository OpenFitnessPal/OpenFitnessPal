#ifndef GOALSPAGE_H
#define GOALSPAGE_H

#include <QWidget>

namespace Ui {
class GoalsPage;
}

class GoalsPage : public QWidget
{
    Q_OBJECT

public:
    explicit GoalsPage(QWidget *parent = nullptr);
    ~GoalsPage();

public slots:
    void carbsChanged(const int value);
    void fatChanged(const int value);
    void proteinChanged(const int value);
    void fiberChanged(const int value);
    void sugarChanged(const int value);
    void satChanged(const int value);
    void monoChanged(const int value);
    void polyChanged(const int value);
    void transChanged(const int value);
    void calciumChanged(const int value);
    void ironChanged(const int value);
    void vitaminAChanged(const int value);
    void vitaminCChanged(const int value);
    void vitaminDChanged(const int value);
    void sodiumChanged(const int value);
    void potassiumChanged(const int value);
    void cholesterolChanged(const int value);

    void goalChanged(int value);
    void caloriesChanged(int value);
    void weightChanged(double value);

    bool recalcGoal();

private:
    Ui::GoalsPage *ui;

    bool m_first = true;

    void saveField(QString field, QVariant variant);
    bool verifyMacros();
};

#endif // GOALSPAGE_H
