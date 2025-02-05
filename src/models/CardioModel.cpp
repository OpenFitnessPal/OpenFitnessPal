#include "CardioModel.h"

#include <QJsonArray>
#include <QJsonObject>

CardioModel::CardioModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_date = QDate::currentDate();

    m_manager = new CardioManager(this);
}

int CardioModel::rowCount(const QModelIndex &parent) const
{
    return m_data.count();
}

QVariant CardioModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int i = index.row();
    Cardio c = m_data[i];
    switch (role) {
    case NAME:
        return c.name();
    case TIME:
        return c.minutes();
    case CALS:
        return c.calories();
    case IDX:
        return i;
    default:
        return QVariant();
    }
}

bool CardioModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        Cardio &c = m_data[index.row()];
        switch (role) {
        case NAME:
            c.setName(value.toString());
            break;
        case TIME:
            c.setMinutes(value.toInt());
            break;
        case CALS:
            c.setCalories(value.toInt());
            break;
        default:
            return false;
        }

        save();
        resetCalories();
        emit dataChanged(index, index, {role});
        return true;
    }

    return false;
}

void CardioModel::add(const Cardio &e, bool doSave)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data << e;
    endInsertRows();

    resetCalories();

    if (doSave) save();
}

void CardioModel::add(const QList<Cardio> &e)
{
    for (const Cardio &ex : e) {
        add(ex, true);
    }
}

void CardioModel::add(QString name, bool doSave)
{
    Cardio ex(this);
    ex.setName(name);
    ex.setCalories(0);
    ex.setMinutes(0);
    add(ex, doSave);
}

bool CardioModel::remove(int row)
{
    beginRemoveRows(QModelIndex(), row, row);
    m_data.remove(row);
    endRemoveRows();

    save();

    resetCalories();

    return true;
}

void CardioModel::clear()
{
    beginResetModel();
    m_data.clear();
    resetCalories();
    endResetModel();
}

void CardioModel::save()
{
    m_manager->save(m_data);
}

void CardioModel::load()
{
    clear();
    QList<Cardio> Cardios = m_manager->load();

    for (const Cardio &e : Cardios) {
        add(e, false);
    }
}

CardioModel *CardioModel::fromJson(const QJsonArray &arr, QObject *parent)
{
    CardioModel *model = new CardioModel(parent);
    for (QJsonValueConstRef ref : arr) {
        QJsonObject obj = ref.toObject();
        Cardio ex = Cardio::fromJson(obj);

        model->add(ex, false);
    }

    return model;
}

QJsonArray CardioModel::toJson() const
{
    QJsonArray arr;
    for (const Cardio &ex : m_data) {
        QJsonObject obj = ex.toJson();
        arr.append(obj);
    }

    return arr;
}

QList<Cardio> CardioModel::data() const
{
    return m_data;
}

QDate CardioModel::date() const
{
    return m_date;
}

void CardioModel::setDate(const QDate &newDate)
{
    if (m_date == newDate)
        return;

    m_manager->setDate(newDate);
    m_date = newDate;

    load();

    emit dateChanged();
}

QHash<int, QByteArray> CardioModel::roleNames() const
{
    QHash<int,QByteArray> rez;
    rez[NAME] = "name";
    rez[TIME] = "time";
    rez[CALS] = "cals";
    rez[IDX] = "idx";
    return rez;
}

double CardioModel::calories() const
{
    return m_calories;
}


void CardioModel::resetCalories()
{
    double sum = 0;
    for (const Cardio &c : m_data) {
        sum += c.calories();
    }
    m_calories = sum;
    emit caloriesChanged();
}
