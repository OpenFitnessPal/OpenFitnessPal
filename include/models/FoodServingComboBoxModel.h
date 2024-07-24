#ifndef FOODSERVINGCOMBOBOXMODEL_H
#define FOODSERVINGCOMBOBOXMODEL_H

#include "ServingSize.h"
#include <QAbstractListModel>
#include <QQmlEngine>

class FoodServingComboBoxModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
public:

    enum FSMRoleTypes
    {
        NAME = Qt::UserRole+1,
        SIZE
    };

    FoodServingComboBoxModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    Q_INVOKABLE void add(const ServingSize &size);
    Q_INVOKABLE void add(const QList<ServingSize> &sizes);

    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    Q_INVOKABLE void clear();

protected:
    QHash<int, QByteArray> roleNames() const override;
private:
    QList<ServingSize> m_data;
};

#endif // FOODSERVINGCOMBOBOXMODEL_H
