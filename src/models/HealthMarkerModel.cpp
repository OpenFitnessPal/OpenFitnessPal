#include "models/HealthMarkerModel.h"

#include <CacheManager.h>

HealthMarkerModel::HealthMarkerModel(QObject *parent)
    : QAbstractListModel{parent}
{
    m_manager = new HealthMarkerManager(this);

    resetOptions();
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
    case IDX:
        return index.row();
    }

    return QVariant();
}

void HealthMarkerModel::add(const QString &name, bool doSave)
{
    HealthMarker marker;
    marker.name = name;

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data << marker;
    endInsertRows();

    if (doSave) save();

    resetOptions();
}

void HealthMarkerModel::remove(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    m_data.remove(index);
    save();
    endRemoveRows();

    resetOptions();
}

bool HealthMarkerModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || data(index, role).toJsonValue() == value.toJsonValue()) {
        return false;
    }

    HealthMarker &h = m_data[index.row()];

    switch (role) {
    case VALUE:
        h.value = value;
        break;
    default:
        return false;
    }

    emit dataChanged(index, index, {role});
    save();
    resetOptions();

    return true;
}

void HealthMarkerModel::save()
{
    m_manager->save(m_data);
}

void HealthMarkerModel::load()
{
    beginResetModel();
    m_data.clear();

    m_data.append(m_manager->load());
    endResetModel();

    resetOptions();
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

void HealthMarkerModel::resetOptions()
{
    auto prev = m_options;
    m_options.clear();
    QStringList tmp;
    tmp << "Resting HR"
        << "Mile Time"
        << "Sleep"
        << "Blood Pressure"
        << "VO2 Max";

    QStringList usedList = used();

    for (const QString &s : std::as_const(tmp)) {
        if (!usedList.contains(s)) {
            m_options.append(s);
        }
    }

    if (prev != m_options) emit optionsChanged();
}

QList<QString> HealthMarkerModel::options() const
{
    return m_options;
}

QHash<int, QByteArray> HealthMarkerModel::roleNames() const
{
    QHash<int,QByteArray> rez;
    rez[VALUE] = "value";
    rez[NAME] = "name";
    rez[IDX] = "idx";
    return rez;
}

QStringList HealthMarkerModel::used()
{
    QStringList used;
    for (const HealthMarker &h : std::as_const(m_data)) {
        used << h.name;
    }

    return used;
}

