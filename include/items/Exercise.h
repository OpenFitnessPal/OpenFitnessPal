#ifndef EXERCISE_H
#define EXERCISE_H

#include "items/ExerciseSet.h"
#include <QWidget>

namespace Ui {
class Exercise;
}

class Exercise : public QWidget
{
    Q_OBJECT

public:
    explicit Exercise(QWidget *parent = nullptr);
    ~Exercise();

public slots:
    void addSet();
    void deleteRequested();

signals:
    void removeRequested();

private:
    Ui::Exercise *ui;

    QList<ExerciseSet *> m_sets;
};

#endif // EXERCISE_H
