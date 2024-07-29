#include "ExerciseSetsModel.h"

ExerciseSetsModel::ExerciseSetsModel(QObject *parent)
    : QAbstractListModel{parent}
{

}

int ExerciseSetsModel::rowCount(const QModelIndex &parent) const
{
    return m_data.size();
}

int ExerciseSetsModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant ExerciseSetsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == ESMRoleTypes::REPS) {
        return m_data[index.row()].reps();
    } else if (role == ESMRoleTypes::WEIGHT) {
        return m_data[index.row()].weight();
    } else if (role == ESMRoleTypes::ID) {
        return index.row();
    }

    return QVariant();
}

QList<ExerciseSet> ExerciseSetsModel::sets()
{
    return m_data;
}

void ExerciseSetsModel::setData(const QList<ExerciseSet> &newData)
{
    beginResetModel();
    m_data.clear();
    endResetModel();

    for (const ExerciseSet &s : newData) {
        add(s.reps(), s.weight());
    }
}

QList<ExerciseSet> ExerciseSetsModel::data()
{
    return m_data;
}

void ExerciseSetsModel::clear()
{
    removeRows(0, m_data.size());
}

void ExerciseSetsModel::duplicateLast()
{
    ExerciseSet e;
    if (!m_data.empty()) {
        e = m_data.last();
    }

    add(e);
}

bool ExerciseSetsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
        return false;
    }

    if (role == ESMRoleTypes::REPS) {
        m_data[index.row()].setReps(value.toInt());
    } else if (role == ESMRoleTypes::WEIGHT) {
        m_data[index.row()].setWeight(value.toInt());
    } else {
        return false;
    }

    return true;
}

Qt::ItemFlags ExerciseSetsModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

void ExerciseSetsModel::add(int reps, int weight)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    ExerciseSet s;
    s.setReps(reps);
    s.setWeight(weight);

    m_data << s;

    endInsertRows();

}

void ExerciseSetsModel::add(const ExerciseSet &set)
{
    add(set.reps(), set.weight());
}

bool ExerciseSetsModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (count == 0) return false;

    beginRemoveRows(parent, row, row + count - 1);
    m_data.remove(row, count);
    endRemoveRows();

    return true;
}

QHash<int, QByteArray> ExerciseSetsModel::roleNames() const
{
    QHash<int, QByteArray> rez;
    rez[REPS] = "reps";
    rez[WEIGHT] = "weight";
    rez[ID] = "setID";
    return rez;
}
