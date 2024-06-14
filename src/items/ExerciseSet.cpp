#include "items/ExerciseSet.h"
#include "ui_ExerciseSet.h"

#include <QTime>

ExerciseSet::ExerciseSet(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ExerciseSet)
{
    ui->setupUi(this);
}

ExerciseSet::ExerciseSet(ExerciseSet *other)
    : QWidget(other->parentWidget())
    , ui(new Ui::ExerciseSet)
{
    ui->setupUi(this);

    qDebug() << other->reps() << other->weight();

    setReps(other->reps());
    setWeight(other->weight());
    setTime(other->time());
}

ExerciseSet::~ExerciseSet()
{
    delete ui;
}

void ExerciseSet::setReps(const int reps)
{
    ui->reps->setValue(reps);
}

int ExerciseSet::reps() const
{
    return ui->reps->value();
}

void ExerciseSet::setWeight(const int weight)
{
    ui->weight->setValue(weight);
}

int ExerciseSet::weight() const
{
    return ui->weight->value();
}

void ExerciseSet::setTime(const QTime &time)
{
    ui->time->setTime(time);
}

QTime ExerciseSet::time() const
{
    return ui->time->time();
}

void ExerciseSet::remove()
{
    emit removeRequested();
}
