#ifndef EXERCISEMODEL_H
#define EXERCISEMODEL_H

#include "Exercise.h"
#include "ExerciseManager.h"
#include "ExerciseSetsModel.h"
#include <QAbstractListModel>

class ExerciseModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    enum EMRoleTypes {
        NAME = Qt::UserRole + 1,
        SETS,
        IDX
    };

    explicit ExerciseModel(QObject *parent = nullptr, bool saveable = true);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    // Add data:
    Q_INVOKABLE void add(const Exercise &e, ExerciseSetsModel *sets, bool doSave = true);
    Q_INVOKABLE void add(const QList<Exercise> &e);
    Q_INVOKABLE void add(const Exercise &e, bool doSave = true);
    Q_INVOKABLE void add(QString name, bool doSave = true);
    Q_INVOKABLE bool remove(int row);

    void clear();
    void save();

    Q_INVOKABLE void load();
    QDate date() const;
    void setDate(const QDate &newDate);

    ExerciseModel *fromJson(const QJsonArray &arr, QObject *parent);
    QJsonArray toJson() const;

    Q_INVOKABLE QList<Exercise> data() const;
signals:
    void dateChanged();

    void needsSave();

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<Exercise> m_data;
    QList<ExerciseSetsModel *> m_sets;

    ExerciseManager *m_manager;

    bool m_saveable;

    QDate m_date;
    Q_PROPERTY(QDate date READ date WRITE setDate NOTIFY dateChanged FINAL)
};

#endif // EXERCISEMODEL_H
