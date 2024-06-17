#include "pages/ExercisePage.h"
#include "items/Exercise.h"
#include "ui_ExercisePage.h"

#include "data/DataManager.h"

ExercisePage::ExercisePage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ExercisePage)
{
    ui->setupUi(this);

    setDate(QDate::currentDate());
}

ExercisePage::~ExercisePage()
{
    delete ui;
}

void ExercisePage::addExercise()
{
    Exercise *exercise = new Exercise(this);

    addExercise(exercise);
}

void ExercisePage::addExercise(Exercise *exercise)
{
    m_exercises.append(exercise);

    DataManager::saveExercises(m_exercises, m_date);

    connect(exercise, &Exercise::removeRequested, this, [this, exercise] {
        DataManager::saveExercises(m_exercises, m_date);

        ui->exerciseLayout->removeWidget(exercise);
        exercise->deleteLater();
        m_exercises.removeOne(exercise);
    });

    connect(exercise, &Exercise::dataChanged, this, [this, exercise] {
        DataManager::saveExercises(m_exercises, m_date);
    });

    ui->exerciseLayout->addWidget(exercise);

}

void ExercisePage::setDate(const QDate &newDate)
{
    m_date = newDate;

    for (Exercise *exercise : m_exercises) {
        ui->exerciseLayout->removeWidget(exercise);
        exercise->deleteLater();
        m_exercises.removeOne(exercise);
    }

    QList<Exercise *> exercises = DataManager::loadExercises(this, newDate);

    for (Exercise *ex : exercises) {
        addExercise(ex);
    }
}
