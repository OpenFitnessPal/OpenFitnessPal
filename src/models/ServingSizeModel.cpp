#include "models/ServingSizeModel.h"

ServingSizeModel::ServingSizeModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

int ServingSizeModel::rowCount(const QModelIndex &parent) const
{
    return m_data.count();
}

int ServingSizeModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant ServingSizeModel::data(const QModelIndex &index, int role) const
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

void ServingSizeModel::add(const ServingSize &size)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data.append(size);
    endInsertRows();

}

void ServingSizeModel::add(const QList<ServingSize> &sizes)
{
    for (const ServingSize &s : sizes) {
        add(s);
    }
}

int ServingSizeModel::indexOf(const ServingSize &size)
{
    return m_data.indexOf(size);
}

void ServingSizeModel::clear()
{
    removeRows(0, m_data.count());
}

bool ServingSizeModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (count == 0) return false;

    beginRemoveRows(parent, row, row + count - 1);
    m_data.remove(row, count);
    endRemoveRows();

    return true;
}

QHash<int, QByteArray> ServingSizeModel::roleNames() const
{
    QHash<int,QByteArray> rez;
    rez[SIZE] = "size";
    rez[NAME] = "name";
    return rez;
}
