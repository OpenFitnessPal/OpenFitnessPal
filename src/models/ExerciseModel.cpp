#include "ExerciseModel.h"

#include <QJsonArray>
#include <QJsonObject>

ExerciseModel::ExerciseModel(QObject *parent, bool saveable)
    : QAbstractListModel(parent)
    , m_saveable(saveable)
{
    m_date = QDate::currentDate();

    m_manager = new ExerciseManager(this);
}

int ExerciseModel::rowCount(const QModelIndex &parent) const
{
    return m_data.count();
}

QVariant ExerciseModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int i = index.row();
    switch (role) {
    case NAME:
        return m_data[i].name();
    case SETS:
        return QVariant::fromValue(m_sets[i]);
    case IDX:
        return i;
    default:
        return QVariant();
    }
}

bool ExerciseModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        switch (role) {
        case NAME:
            m_data[index.row()].setName(value.toString());
            break;
        default:
            return false;
        }

        save();
        emit dataChanged(index, index, {role});
    }

    return false;
}

void ExerciseModel::add(const Exercise &e, ExerciseSetsModel *sets, bool doSave)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data << e;
    m_sets << sets;
    endInsertRows();

    connect(sets, &ExerciseSetsModel::save, this, &ExerciseModel::save);

    if (doSave) save();
}

void ExerciseModel::add(const QList<Exercise> &e)
{
    for (const Exercise &ex : e) {
        add(ex, true);
    }
}

void ExerciseModel::add(const Exercise &e, bool doSave)
{
    ExerciseSetsModel *model = new ExerciseSetsModel(this);
    for (const ExerciseSet &s : e.sets()) {
        model->add(s, false);
    }

    add(e, model, doSave);
}

void ExerciseModel::add(QString name, bool doSave)
{
    Exercise ex(this);
    ex.setName(name);
    add(ex, new ExerciseSetsModel(this), doSave);
}

bool ExerciseModel::remove(int row)
{
    beginRemoveRows(QModelIndex(), row, row);
    m_data.remove(row);
    m_sets.remove(row);
    endRemoveRows();

    save();

    return true;
}

void ExerciseModel::clear()
{
    beginResetModel();
    m_data.clear();
    m_sets.clear();
    endResetModel();
}

void ExerciseModel::save()
{
    for (size_t i = 0; i < rowCount(); ++i) {
        m_data[i].setSets(m_sets[i]->data());
    }

    if (!m_saveable) {
        emit needsSave();
    } else {
        m_manager->save(m_data);
    }
}

void ExerciseModel::load()
{
    clear();
    QList<Exercise> exercises = m_manager->load();

    for (const Exercise &e : exercises) {
        add(e, false);
    }
}

ExerciseModel *ExerciseModel::fromJson(const QJsonArray &arr, QObject *parent)
{
    ExerciseModel *model = new ExerciseModel(parent, false);
    for (QJsonValueConstRef ref : arr) {
        QJsonObject obj = ref.toObject();
        Exercise ex = Exercise::fromJson(obj);
        ExerciseSetsModel *sets = ExerciseSetsModel::fromJson(obj.value("sets").toArray(), model);

        model->add(ex, sets, false);
    }

    return model;
}

QJsonArray ExerciseModel::toJson() const
{
    QJsonArray arr;
    for (const Exercise &ex : m_data) {
        QJsonObject obj = ex.toJson();
        arr.append(obj);
    }

    return arr;
}

QList<Exercise> ExerciseModel::data() const
{
    return m_data;
}

QDate ExerciseModel::date() const
{
    return m_date;
}

void ExerciseModel::setDate(const QDate &newDate)
{
    if (m_date == newDate)
        return;
    m_manager->setDate(newDate);
    m_date = newDate;

    load();

    emit dateChanged();
}

QHash<int, QByteArray> ExerciseModel::roleNames() const
{
    QHash<int,QByteArray> rez;
    rez[NAME] = "name";
    rez[SETS] = "sets";
    rez[IDX] = "idx";
    return rez;
}
