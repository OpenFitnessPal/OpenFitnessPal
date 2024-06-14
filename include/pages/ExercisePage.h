#ifndef EXERCISEPAGE_H
#define EXERCISEPAGE_H

#include <QWidget>

namespace Ui {
class ExercisePage;
}

class ExercisePage : public QWidget
{
    Q_OBJECT

public:
    explicit ExercisePage(QWidget *parent = nullptr);
    ~ExercisePage();

public slots:
    void addExercise();

private:
    Ui::ExercisePage *ui;
};

#endif // EXERCISEPAGE_H
