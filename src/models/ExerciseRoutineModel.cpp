#include "ExerciseRoutineModel.h"

ExerciseRoutineModel::ExerciseRoutineModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_manager = new RoutineManager(this);
}

int ExerciseRoutineModel::rowCount(const QModelIndex &parent) const
{
    return m_data.count();
}

QVariant ExerciseRoutineModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int i = index.row();
    ExerciseRoutine r = m_data[i];

    switch (role) {
    case NAME:
        return r.name();
    case NOTES:
        return r.notes();
    case EXERCISES:
        return QVariant::fromValue(m_exercises[i]);
    case IDX:
        return i;
    default:
        return QVariant();
    }
}

bool ExerciseRoutineModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        ExerciseRoutine &r = m_data[index.row()];

        switch (role) {
        case NAME:
            r.setName(value.toString());
            break;
        case NOTES:
            r.setNotes(value.toString());
            break;
        default:
            return false;
        }

        save();
        emit dataChanged(index, index, {role});
    }

    return false;
}

void ExerciseRoutineModel::add(const ExerciseRoutine &r, ExerciseModel *exercises, bool doSave)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data << r;
    m_exercises << exercises;
    endInsertRows();

    connect(exercises, &ExerciseModel::needsSave, this, &ExerciseRoutineModel::save);

    if (doSave) save();
}

void ExerciseRoutineModel::add(QString name, bool doSave)
{
    ExerciseRoutine r;
    r.setName(name);
    add(r, new ExerciseModel(this, false), doSave);
}

bool ExerciseRoutineModel::remove(int row)
{
    beginRemoveRows(QModelIndex(), row, row);
    m_data.remove(row);
    m_exercises.remove(row);
    endRemoveRows();

    save();

    return true;
}

void ExerciseRoutineModel::clear()
{
    beginResetModel();
    m_data.clear();
    m_exercises.clear();
    endResetModel();
}

void ExerciseRoutineModel::save()
{
    for (size_t i = 0; i < rowCount(); ++i) {
        m_data[i].setExercises(m_exercises[i]->data());
    }

    m_manager->save(m_data);
}

void ExerciseRoutineModel::load()
{
    clear();
    QList<ExerciseRoutine> routines = m_manager->load();

    for (const ExerciseRoutine &r : routines) {
        ExerciseModel *exercises = new ExerciseModel(this, false);
        for (const Exercise &e : r.exercises()) {
            exercises->add(e, false);
        }

        add(r, exercises, false);
    }
}

QHash<int, QByteArray> ExerciseRoutineModel::roleNames() const
{
    QHash<int,QByteArray> rez;
    rez[NAME] = "name";
    rez[NOTES] = "notes";
    rez[EXERCISES] = "exercises";
    rez[IDX] = "idx";
    return rez;
}




