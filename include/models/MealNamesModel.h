#ifndef MEALNAMESMODEL_H
#define MEALNAMESMODEL_H

#include "MealNamesManager.h"
#include <QAbstractItemModel>

class MealNamesModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum MNMRoleTypes {
        NAME = Qt::UserRole + 1,
        IDX
    };

    MealNamesModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    // Add data:
    Q_INVOKABLE void add(QString name, bool doSave = true);
    Q_INVOKABLE bool remove(int row);
    Q_INVOKABLE bool move(int from, int to);

    void clear();
    void save();

    Q_INVOKABLE void load();

    QDate date() const;
    void setDate(const QDate &newDate);

signals:
    void dateChanged();

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QStringList m_data;
    QDate m_date;

    MealNamesManager *m_manager;
    Q_PROPERTY(QDate date READ date WRITE setDate NOTIFY dateChanged FINAL)
};

#endif // MEALNAMESMODEL_H
