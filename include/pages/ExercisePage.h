#ifndef EXERCISEPAGE_H
#define EXERCISEPAGE_H

#include "items/Exercise.h"
#include <QWidget>
#include <qdatetime.h>

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
    void addExercise(Exercise *exercise);

    void setDate(const QDate &newDate);

private:
    Ui::ExercisePage *ui;

    QList<Exercise *> m_exercises;
    QDate m_date;
};

#endif // EXERCISEPAGE_H
