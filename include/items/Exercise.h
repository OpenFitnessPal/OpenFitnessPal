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

    QList<ExerciseSet *> sets() const;

    void setName(const QString &name);
    QString name();

    void setSets(const QList<ExerciseSet *> &newSets);

public slots:
    void addSet();
    void deleteRequested();

    void change();

signals:
    void removeRequested();

    void dataChanged();

private:
    Ui::Exercise *ui;

    QList<ExerciseSet *> m_sets;
};

#endif // EXERCISE_H
