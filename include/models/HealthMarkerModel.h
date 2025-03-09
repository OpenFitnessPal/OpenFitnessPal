#ifndef HealthMarkerModel_H
#define HealthMarkerModel_H

#include "HealthMarkerManager.h"
#include <QAbstractListModel>
#include <QQmlEngine>

class HealthMarkerModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    enum HMMRoleTypes
    {
        NAME = Qt::UserRole+1,
        VALUE,
        IDX
    };

    HealthMarkerModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    Q_INVOKABLE void add(const QString &name, bool doSave = true);
    Q_INVOKABLE void remove(int index);

    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Q_INVOKABLE void save();
    Q_INVOKABLE void load();

    QDateTime date() const;
    void setDate(const QDateTime &newDate);

    QStringList options() const;
    void resetOptions();

signals:
    void dateChanged();

    void optionsChanged();

protected:
    QHash<int, QByteArray> roleNames() const override;
private:
    QList<HealthMarker> m_data;
    QList<QString> m_options;

    QDateTime m_date;

    HealthMarkerManager *m_manager;
    Q_PROPERTY(QDateTime date READ date WRITE setDate NOTIFY dateChanged FINAL)
    Q_PROPERTY(QStringList options READ options RESET resetOptions NOTIFY optionsChanged FINAL CONSTANT)

    QStringList used();
};

#endif // HealthMarkerModel_H
