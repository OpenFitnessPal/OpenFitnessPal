#include "models/HealthMarkerModel.h"

#include <CacheManager.h>

HealthMarkerModel::HealthMarkerModel(QObject *parent)
    : QAbstractListModel{parent}
{
    m_manager = new HealthMarkerManager(this);
}

int HealthMarkerModel::rowCount(const QModelIndex &parent) const
{
    return m_data.size();
}

int HealthMarkerModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant HealthMarkerModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    HealthMarker h = m_data[index.row()];
    switch (role) {
    case VALUE:
        return h.value;
    case NAME:
        return h.name;
    }

    return QVariant();
}

void HealthMarkerModel::add(const QString &name)
{
    auto markers = m_manager->markers();
    markers.append(name);

    m_manager->set(name, QVariant());

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data << HealthMarker{name, QVariant()};
    endInsertRows();
}

void HealthMarkerModel::remove(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    m_manager->remove(m_data.at(index).name);
    m_data.remove(index);
    endRemoveRows();
}

bool HealthMarkerModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
        return false;
    }

    HealthMarker &h = m_data[index.row()];

    switch (role) {
    case VALUE:
        h.value = value;
        m_manager->set(h.name, h.value);
        break;
    default:
        return false;
    }

    emit dataChanged(index, index, {role});

    return true;
}

void HealthMarkerModel::load()
{
    beginResetModel();
    m_data.clear();

    auto markers = m_manager->getCurrentMarkers();

    m_data.append(markers);
    endResetModel();
}

QDateTime HealthMarkerModel::date() const
{
    return m_date;
}

void HealthMarkerModel::setDate(const QDateTime &newDate)
{
    if (m_date == newDate)
        return;
    m_date = newDate;
    m_manager->setDate(newDate);

    load();
    emit dateChanged();
}

QHash<int, QByteArray> HealthMarkerModel::roleNames() const
{
    QHash<int,QByteArray> rez;
    rez[VALUE] = "value";
    rez[NAME] = "name";
    return rez;
}
