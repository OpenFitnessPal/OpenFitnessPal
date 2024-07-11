#ifndef NUTRIENTPROGRESSBAR_H
#define NUTRIENTPROGRESSBAR_H

#include <QFrame>

namespace Ui {
class NutrientProgressBar;
}

class NutrientProgressBar : public QFrame
{
    Q_OBJECT

public:
    explicit NutrientProgressBar(QWidget *parent = nullptr);
    ~NutrientProgressBar();

    void setTarget(const double newTarget);
    void setTotal(const double newTotal);

    void setUnit(const QString &unit);
    void setName(const QString &name);

private:
    Ui::NutrientProgressBar *ui;

    void reset();

    QString m_unit = "g";
    QString m_name = "";

    double m_total = 0.;
    double m_target = 0.;
};

#endif // NUTRIENTPROGRESSBAR_H
