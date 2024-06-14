#include "items/Exercise.h"
#include "ui_Exercise.h"

#include <QMessageBox>

Exercise::Exercise(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Exercise)
{
    ui->setupUi(this);
}

Exercise::~Exercise()
{
    delete ui;
}

void Exercise::addSet()
{
    ExerciseSet *set;
    qDebug() << m_sets << m_sets.empty();
    if (!m_sets.empty()) {
        set = new ExerciseSet(m_sets.last());
    } else {
        set = new ExerciseSet(this);
    }

    connect(set, &ExerciseSet::removeRequested, this, [this, set] {
        ui->exerciseLayout->removeWidget(set);
        m_sets.removeOne(set);
        set->deleteLater();
    });

    ui->exerciseLayout->insertWidget(m_sets.count(), set, 0, Qt::AlignTop);
    m_sets.append(set);
}

void Exercise::deleteRequested()
{
    QMessageBox::StandardButtons button = QMessageBox::question(this, "Really delete exercise?", "Are you sure you want to delete the exercise " + ui->exerciseName->text() + "?");
    if (button == QMessageBox::Yes) {
        emit removeRequested();
    }
}
