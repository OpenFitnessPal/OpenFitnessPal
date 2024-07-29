#ifndef ExerciseSetsModel_H
#define ExerciseSetsModel_H

#include "ExerciseSet.h"
#include <QAbstractListModel>
#include <QObject>

class ExerciseSetsModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
public:

    enum ESMRoleTypes
    {
        REPS = Qt::UserRole + 1,
        WEIGHT,
        ID
    };

    ExerciseSetsModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    Q_INVOKABLE QList<ExerciseSet> sets();

    Q_INVOKABLE void add(int reps = 0, int weight = 0);
    Q_INVOKABLE void add(const ExerciseSet &set);
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    Q_INVOKABLE void setData(const QList<ExerciseSet> &newData);
    Q_INVOKABLE QList<ExerciseSet> data();

    Q_INVOKABLE void clear();

    Q_INVOKABLE void duplicateLast();

    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<ExerciseSet> m_data;
};

#endif // ExerciseSetsModel_H
