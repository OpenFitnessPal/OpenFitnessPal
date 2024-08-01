#include "models/FoodServingComboBoxModel.h"

#include <DataManager.h>

FoodServingComboBoxModel::FoodServingComboBoxModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

int FoodServingComboBoxModel::rowCount(const QModelIndex &parent) const
{
    return m_data.count();
}

int FoodServingComboBoxModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant FoodServingComboBoxModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_data.count()) {
        return QVariant();
    }

    if (role == FSMRoleTypes::SIZE) {
        return QVariant::fromValue(m_data.at(index.row()));
    } else if (role == FSMRoleTypes::NAME) {
        return m_data.at(index.row()).unit();
    }

    return QVariant();
}

void FoodServingComboBoxModel::add(const ServingSize &size)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data.append(size);
    endInsertRows();

}

void FoodServingComboBoxModel::add(const QList<ServingSize> &sizes)
{
    for (const ServingSize &s : sizes) {
        add(s);
    }
}

int FoodServingComboBoxModel::indexOf(const ServingSize &size)
{
    return m_data.indexOf(size);
}

void FoodServingComboBoxModel::clear()
{
    removeRows(0, m_data.count());
}

bool FoodServingComboBoxModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (count == 0) return false;

    beginRemoveRows(parent, row, row + count - 1);
    m_data.remove(row, count);
    endRemoveRows();

    return true;
}

QHash<int, QByteArray> FoodServingComboBoxModel::roleNames() const
{
    QHash<int,QByteArray> rez;
    rez[SIZE] = "size";
    rez[NAME] = "name";
    return rez;
}
