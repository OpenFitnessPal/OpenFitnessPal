#ifndef EXERCISELISTMODEL_H
#define EXERCISELISTMODEL_H

#include "Exercise.h"
#include <QAbstractListModel>
#include <QObject>

class ExerciseListModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
public:

    enum ELMRoleTypes
    {
        NAME = Qt::UserRole+1,
        SETS,
        ID
    };

    ExerciseListModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    Q_INVOKABLE void add(QString name = "", QList<ExerciseSet> sets = {});
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    Q_INVOKABLE void clear();

    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Q_INVOKABLE void loadData(QDate date);
    Q_INVOKABLE void saveData(QDate date);

    Qt::ItemFlags flags(const QModelIndex &index) const override;

protected:
    QHash<int, QByteArray> roleNames() const override;
private:
    QList<Exercise> m_data;
};

#endif // EXERCISELISTMODEL_H
