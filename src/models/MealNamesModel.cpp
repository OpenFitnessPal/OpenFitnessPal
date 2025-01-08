#include "models/MealNamesModel.h"

MealNamesModel::MealNamesModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_date = QDate::currentDate();

    m_manager = new MealNamesManager(this);
}

int MealNamesModel::rowCount(const QModelIndex &parent) const
{
    return m_data.count();
}

QVariant MealNamesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
    case NAME:
        return m_data[index.row()];
    case IDX:
        return index.row();
    default:
        return m_data[index.row()];
    }
}

bool MealNamesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        switch (role) {
        case NAME:
            m_data[index.row()] = value.toString();
            break;
        default:
            break;
        }

        save();
        emit dataChanged(index, index, {role});
    }

    return false;
}

void MealNamesModel::add(QString name, bool doSave)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data << name;
    endInsertRows();

    if (doSave) save();
}

bool MealNamesModel::remove(int row)
{
    beginRemoveRows(QModelIndex(), row, row);
    m_data.remove(row);
    endRemoveRows();

    save();

    return true;
}

bool MealNamesModel::move(int from, int to)
{
    int dest = (from < to) ? to + 1 : to;

    beginMoveRows(QModelIndex(), from, from, QModelIndex(), dest);
    m_data.move(from, to);
    endMoveRows();

    save();

    return true;
}

void MealNamesModel::clear()
{
    beginResetModel();
    m_data.clear();
    endResetModel();
}

void MealNamesModel::save()
{
    m_manager->setMealNames(m_data);
    m_manager->save();
}

void MealNamesModel::load()
{
    m_manager->load();

    for (const QString &s : m_manager->mealNames()) {
        add(s, false);
    }
}

QHash<int, QByteArray> MealNamesModel::roleNames() const
{
    QHash<int,QByteArray> rez;
    rez[NAME] = "name";
    rez[IDX] = "idx";

    return rez;
}

QDate MealNamesModel::date() const
{
    return m_date;
}

void MealNamesModel::setDate(const QDate &newDate)
{
    if (m_date == newDate)
        return;
    m_date = newDate;
    emit dateChanged();

    clear();

    m_manager->setDate(newDate);

    load();
}
