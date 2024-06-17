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
    if (!m_sets.empty()) {
        set = new ExerciseSet(m_sets.last());
    } else {
        set = new ExerciseSet(this);
    }

    connect(set, &ExerciseSet::removeRequested, this, [this, set] {
        ui->exerciseLayout->removeWidget(set);
        m_sets.removeOne(set);
        set->deleteLater();

        emit dataChanged();
    });

    connect(set, &ExerciseSet::dataChanged, this, &Exercise::dataChanged);

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

void Exercise::change()
{
    emit dataChanged();
}

void Exercise::setSets(const QList<ExerciseSet *> &newSets)
{
    m_sets = newSets;

    int i = 0;
    for (ExerciseSet *set : newSets) {
        ui->exerciseLayout->insertWidget(i, set, 0, Qt::AlignTop);
        ++i;

        connect(set, &ExerciseSet::removeRequested, this, [this, set] {
            ui->exerciseLayout->removeWidget(set);
            m_sets.removeOne(set);
            set->deleteLater();

            emit dataChanged();
        });

        connect(set, &ExerciseSet::dataChanged, this, &Exercise::dataChanged);

    }
}

QList<ExerciseSet *> Exercise::sets() const
{
    return m_sets;
}

void Exercise::setName(const QString &name)
{
    ui->exerciseName->setText(name);
}

QString Exercise::name()
{
    return ui->exerciseName->text();
}
