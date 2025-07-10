#include "ExerciseSetsModel.h"

#include <QJsonArray>
#include <QJsonObject>

ExerciseSetsModel::ExerciseSetsModel(QObject *parent)
    : QAbstractListModel(parent)
{}

int ExerciseSetsModel::rowCount(const QModelIndex &parent) const
{
    return m_data.count();
}

QVariant ExerciseSetsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    ExerciseSet set = m_data[index.row()];
    switch (role) {
    case REPS:
        return set.reps();
    case WEIGHT:
        return set.weight();
    case IDX:
        return index.row();
    default:
        return QVariant();
    }
}


bool ExerciseSetsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        switch (role) {
        case REPS:
            m_data[index.row()].setReps(value.toInt());
            break;
        case WEIGHT:
            m_data[index.row()].setWeight(value.toInt());
            break;
        default:
            break;
        }

        emit dataChanged(index, index, {role});
        emit save();
    }

    return false;

}

void ExerciseSetsModel::add(const ExerciseSet &set, bool doSave)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data << set;
    endInsertRows();

    if (doSave) {
        emit save();
    }
}

void ExerciseSetsModel::add(bool doSave)
{
    ExerciseSet set;
    if (!m_data.isEmpty()) {
        set = m_data.last();
    }

    add(set, doSave);
}

bool ExerciseSetsModel::remove(int row)
{
    beginRemoveRows(QModelIndex(), row, row);
    m_data.remove(row);
    endRemoveRows();

    emit save();

    return true;
}

ExerciseSetsModel *ExerciseSetsModel::fromJson(const QJsonArray &arr, QObject *parent)
{
    ExerciseSetsModel *model = new ExerciseSetsModel(parent);
    for (QJsonValueConstRef ref : arr) {
        ExerciseSet set = ExerciseSet::fromJson(ref.toObject());

        model->add(set, false);
    }

    return model;
}

QJsonArray ExerciseSetsModel::toJson() const
{
    QJsonArray arr;
    for (const ExerciseSet &set : m_data) {
        QJsonObject obj = set.toJson();
        arr.append(obj);
    }

    return arr;
}



QHash<int, QByteArray> ExerciseSetsModel::roleNames() const
{
    QHash<int,QByteArray> rez;
    rez[REPS] = "reps";
    rez[WEIGHT] = "weight";
    rez[IDX] = "idx";
    return rez;
}



QList<ExerciseSet> ExerciseSetsModel::data()
{
    return m_data;
}

