#include "ExerciseListModel.h"
#include "DataManager.h"

ExerciseListModel::ExerciseListModel(QObject *parent)
    : QAbstractListModel{parent}
{

}

int ExerciseListModel::rowCount(const QModelIndex &parent) const
{
    return m_data.size();
}

int ExerciseListModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant ExerciseListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == ELMRoleTypes::NAME) {
        return m_data[index.row()].name();
    } else if (role == ELMRoleTypes::SETS) {
        return QVariant::fromValue(m_data[index.row()].sets());
    } else if (role == ELMRoleTypes::ID) {
        return index.row();
    }

    return QVariant();
}

void ExerciseListModel::setExercises(const QList<Exercise> &exercises)
{
    beginResetModel();
    m_data.clear();
    endResetModel();

    addMultiple(exercises);
}

QList<Exercise> ExerciseListModel::exercises()
{
    return m_data;
}

void ExerciseListModel::addMultiple(const QList<Exercise> &exercises)
{
    for (const Exercise &e : exercises) {
        add(e.name(), e.sets());
    }
}

void ExerciseListModel::loadData(QDate date)
{
    auto exercises = DataManager::loadExercises(date);
    setExercises(exercises);
}

void ExerciseListModel::saveData(QDate date)
{
    DataManager::truncateSaveExercises(m_data, date);
}

void ExerciseListModel::add(QString name, QList<ExerciseSet> sets)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    Exercise e;

    e.setName(name);
    e.setSets(sets);

    m_data << e;
    endInsertRows();

}

bool ExerciseListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (count == 0) return false;


    beginRemoveRows(parent, row, row + count - 1);
    m_data.remove(row, count);
    endRemoveRows();

    return true;
}

void ExerciseListModel::clear()
{
    removeRows(0, m_data.count());
}

bool ExerciseListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
        return false;
    }

    if (role == ELMRoleTypes::NAME) {
        m_data[index.row()].setName(value.toString());
    } else if (role == ELMRoleTypes::SETS) {
        m_data[index.row()].setSets(value.value<QList<ExerciseSet>>());
    } else {
        return false;
    }

    return true;
}

Qt::ItemFlags ExerciseListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

QHash<int, QByteArray> ExerciseListModel::roleNames() const
{
    QHash<int,QByteArray> rez;
    rez[NAME] = "name";
    rez[SETS] = "sets";
    rez[ID] = "exID";
    return rez;
}
