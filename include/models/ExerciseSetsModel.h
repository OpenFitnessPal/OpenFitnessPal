#ifndef EXERCISESETSMODEL_H
#define EXERCISESETSMODEL_H

#include "ExerciseSet.h"
#include <QAbstractListModel>

class ExerciseSetsModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum ESMRoleTypes {
        REPS = Qt::UserRole + 1,
        WEIGHT,
        IDX
    };

    explicit ExerciseSetsModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    // Add data:
    Q_INVOKABLE void add(const ExerciseSet &set, bool doSave = true);
    Q_INVOKABLE void add(bool doSave = true);
    Q_INVOKABLE bool remove(int row);

    static ExerciseSetsModel *fromJson(const QJsonArray &arr, QObject *parent);
    QJsonArray toJson() const;

    QList<ExerciseSet> data();

signals:
    void save();

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<ExerciseSet> m_data;
};

Q_DECLARE_METATYPE(ExerciseSetsModel)

#endif // EXERCISESETSMODEL_H
