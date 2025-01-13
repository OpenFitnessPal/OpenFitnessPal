#ifndef EXERCISEROUTINEMODEL_H
#define EXERCISEROUTINEMODEL_H

#include "ExerciseModel.h"
#include "ExerciseRoutine.h"
#include "RoutineManager.h"
#include <QAbstractListModel>
#include <qqmlintegration.h>

class ExerciseRoutineModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    enum EMRoleTypes {
        NAME = Qt::UserRole + 1,
        NOTES,
        EXERCISES,
        IDX
    };
    explicit ExerciseRoutineModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    // add data
    Q_INVOKABLE void add(const ExerciseRoutine &r, ExerciseModel *exercises, bool doSave = true);
    Q_INVOKABLE void add(QString name, bool doSave = true);
    Q_INVOKABLE bool remove(int row);

    void clear();
    void save();

    Q_INVOKABLE void load();

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<ExerciseRoutine> m_data;
    QList<ExerciseModel *> m_exercises;

    RoutineManager *m_manager;
};

#endif // EXERCISEROUTINEMODEL_H
