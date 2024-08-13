#include "ExerciseRoutinesModel.h"
#include "DataManager.h"

ExerciseRoutinesModel::ExerciseRoutinesModel(QObject *parent)
    : QAbstractListModel{parent}
{

}

int ExerciseRoutinesModel::rowCount(const QModelIndex &parent) const
{
    return m_data.size();
}

int ExerciseRoutinesModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant ExerciseRoutinesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == ELMRoleTypes::NAME) {
        return m_data[index.row()].name();
    } if (role == ELMRoleTypes::NOTES) {
        return m_data[index.row()].notes();
    } else if (role == ELMRoleTypes::EXERCISES) {
        return QVariant::fromValue(m_data[index.row()].exercises());
    } else if (role == ELMRoleTypes::ID) {
        return index.row();
    }

    return QVariant();
}

void ExerciseRoutinesModel::add(QString name, QString notes, QList<Exercise> exercises)
{
    ExerciseRoutine r;
    r.setName(name);
    r.setNotes(notes);
    r.setExercises(exercises);

    add(r);
}

void ExerciseRoutinesModel::add(const ExerciseRoutine &routine)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data.append(routine);
    endInsertRows();
}

void ExerciseRoutinesModel::loadData()
{
    beginResetModel();
    m_data.clear();
    endResetModel();

    auto routines = DataManager::loadRoutines();

    for(const ExerciseRoutine &e : routines) {
        add(e);
    }
}

void ExerciseRoutinesModel::saveData()
{
    DataManager::truncateSaveRoutines(m_data);
}

bool ExerciseRoutinesModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (count == 0) return false;

    beginRemoveRows(parent, row, row + count - 1);
    m_data.remove(row, count);
    endRemoveRows();

    return true;
}

void ExerciseRoutinesModel::clear()
{
    removeRows(0, m_data.count());
}

bool ExerciseRoutinesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
        return false;
    }

    if (role == ELMRoleTypes::NAME) {
        m_data[index.row()].setName(value.toString());
    } else if (role == ELMRoleTypes::NOTES) {
        m_data[index.row()].setNotes(value.toString());
    } else if (role == ELMRoleTypes::EXERCISES) {
        m_data[index.row()].setExercises(value.value<QList<Exercise>>());
    } else {
        return false;
    }

    return true;
}

Qt::ItemFlags ExerciseRoutinesModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

QHash<int, QByteArray> ExerciseRoutinesModel::roleNames() const
{
    QHash<int,QByteArray> rez;
    rez[NAME] = "name";
    rez[NOTES] = "notes";
    rez[EXERCISES] = "exercises";
    rez[ID] = "exID";
    return rez;
}
