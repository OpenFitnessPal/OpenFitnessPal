#ifndef EXERCISESET_H
#define EXERCISESET_H

#include <QWidget>

namespace Ui {
class ExerciseSet;
}

class ExerciseSet : public QWidget
{
    Q_OBJECT

public:
    explicit ExerciseSet(QWidget *parent = nullptr);
    ExerciseSet(ExerciseSet *other);
    ~ExerciseSet();

    void setReps(const int reps);
    int reps() const;

    void setWeight(const int weight);
    int weight() const;

    void setTime(const QTime &time);
    QTime time() const;

public slots:
    void remove();

signals:
    void removeRequested();

private:
    Ui::ExerciseSet *ui;
};

#endif // EXERCISESET_H
