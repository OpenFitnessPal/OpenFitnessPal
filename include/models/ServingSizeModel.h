#ifndef SERVINGSIZEMODEL_H
#define SERVINGSIZEMODEL_H

#include <QAbstractItemModel>

#include "ServingSize.h"
#include <QAbstractListModel>
#include <QQmlEngine>

class ServingSizeModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
public:

    enum FSMRoleTypes
    {
        NAME = Qt::UserRole+1,
        SIZE
    };

    ServingSizeModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    Q_INVOKABLE void add(const ServingSize &size);
    Q_INVOKABLE void add(const QList<ServingSize> &sizes);

    Q_INVOKABLE int indexOf(const ServingSize &size);

    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    Q_INVOKABLE void clear();

protected:
    QHash<int, QByteArray> roleNames() const override;
private:
    QList<ServingSize> m_data;
};

#endif // SERVINGSIZEMODEL_H
