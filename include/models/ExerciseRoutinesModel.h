#ifndef EXERCISEROUTINESMODEL_H
#define EXERCISEROUTINESMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <QQmlEngine>

#include "ExerciseRoutine.h"

class ExerciseRoutinesModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
public:

    enum ELMRoleTypes
    {
        NAME = Qt::UserRole+1,
        NOTES,
        EXERCISES,
        ID
    };

    ExerciseRoutinesModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    Q_INVOKABLE void add(QString name = "", QString notes = "", QList<Exercise> exercises = {});
    Q_INVOKABLE void add(const ExerciseRoutine &routine);
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    Q_INVOKABLE void clear();

    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Q_INVOKABLE void loadData();
    Q_INVOKABLE void saveData();

    Qt::ItemFlags flags(const QModelIndex &index) const override;

protected:
    QHash<int, QByteArray> roleNames() const override;
private:
    QList<ExerciseRoutine> m_data;
};

#endif // EXERCISEROUTINESMODEL_H
