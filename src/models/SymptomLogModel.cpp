#include "SymptomLogModel.h"

#include <QJsonArray>
#include <QJsonObject>

SymptomLogModel::SymptomLogModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_date = QDateTime::currentDateTime();

    m_manager = new SymptomLogManager(this);
}

int SymptomLogModel::rowCount(const QModelIndex &parent) const
{
    return m_data.count();
}

QVariant SymptomLogModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int i = index.row();
    SymptomLog s = m_data[i];

    switch (role) {
    case MESSAGE:
        return s.message();
    case TIME:
        return s.time();
    case IDX:
        return i;
    default:
        return QVariant();
    }
}

bool SymptomLogModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        SymptomLog &s = m_data[index.row()];
        switch (role) {
        case MESSAGE:
            s.setMessage(value.toString());
            break;
        case TIME:
            s.setTime(value.toTime());
            break;
        default:
            return false;
        }

        save();
        emit dataChanged(index, index, {role});
        return true;
    }

    return false;
}

void SymptomLogModel::add(const SymptomLog &e, bool doSave)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data << e;
    endInsertRows();

    if (doSave) save();
}

void SymptomLogModel::add(const QList<SymptomLog> &e)
{
    for (const SymptomLog &ex : e) {
        add(ex, true);
    }
}

void SymptomLogModel::add(bool doSave)
{
    SymptomLog sl;
    sl.setMessage("");
    sl.setTime(QTime::currentTime());
    add(sl, doSave);
}

bool SymptomLogModel::remove(int row)
{
    beginRemoveRows(QModelIndex(), row, row);
    m_data.remove(row);
    endRemoveRows();

    save();

    return true;
}

void SymptomLogModel::clear()
{
    beginResetModel();
    m_data.clear();
    endResetModel();
}

void SymptomLogModel::save()
{
    m_manager->save(m_data);
}

void SymptomLogModel::load()
{
    clear();
    QList<SymptomLog> SymptomLogs = m_manager->load();

    for (const SymptomLog &e : SymptomLogs) {
        add(e, false);
    }
}

SymptomLogModel *SymptomLogModel::fromJson(const QJsonArray &arr, QObject *parent)
{
    SymptomLogModel *model = new SymptomLogModel(parent);
    for (QJsonValueConstRef ref : arr) {
        QJsonObject obj = ref.toObject();
        SymptomLog ex = SymptomLog::fromJson(obj);

        model->add(ex, false);
    }

    return model;
}

QJsonArray SymptomLogModel::toJson() const
{
    QJsonArray arr;
    for (const SymptomLog &ex : m_data) {
        QJsonObject obj = ex.toJson();
        arr.append(obj);
    }

    return arr;
}

QList<SymptomLog> SymptomLogModel::data() const
{
    return m_data;
}

QDateTime SymptomLogModel::date() const
{
    return m_date;
}

void SymptomLogModel::setDate(const QDateTime &newDate)
{
    if (m_date == newDate)
        return;

    m_manager->setDate(newDate);
    m_date = newDate;

    load();

    emit dateChanged();
}

QHash<int, QByteArray> SymptomLogModel::roleNames() const
{
    QHash<int,QByteArray> rez;
    rez[MESSAGE] = "message";
    rez[TIME] = "time";
    rez[IDX] = "idx";
    return rez;
}
