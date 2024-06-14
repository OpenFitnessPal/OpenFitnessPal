#include "pages/ExercisePage.h"
#include "items/Exercise.h"
#include "ui_ExercisePage.h"

ExercisePage::ExercisePage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ExercisePage)
{
    ui->setupUi(this);
}

ExercisePage::~ExercisePage()
{
    delete ui;
}

void ExercisePage::addExercise()
{
    Exercise *exercise = new Exercise(this);

    connect(exercise, &Exercise::removeRequested, this, [this, exercise] {
        ui->exerciseLayout->removeWidget(exercise);
        exercise->deleteLater();
    });

    ui->exerciseLayout->addWidget(exercise);
}
