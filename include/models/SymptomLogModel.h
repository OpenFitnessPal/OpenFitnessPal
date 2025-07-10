#ifndef SYMPTOMLOGMODEL_H
#define SYMPTOMLOGMODEL_H

#include <QAbstractListModel>

#include <QAbstractItemModel>

#include "SymptomLog.h"
#include "SymptomLogManager.h"

class SymptomLogModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    enum SLMRoleTypes {
        MESSAGE = Qt::UserRole + 1,
        TIME,
        IDX
    };

    explicit SymptomLogModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    // Add data:
    Q_INVOKABLE void add(const SymptomLog &e, bool doSave = true);
    Q_INVOKABLE void add(const QList<SymptomLog> &e);
    Q_INVOKABLE void add(bool doSave = true);
    Q_INVOKABLE bool remove(int row);

    void clear();
    void save();

    Q_INVOKABLE void load();
    QDateTime date() const;
    void setDate(const QDateTime &newDate);

    SymptomLogModel *fromJson(const QJsonArray &arr, QObject *parent);
    QJsonArray toJson() const;

    Q_INVOKABLE QList<SymptomLog> data() const;

signals:
    void dateChanged();

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<SymptomLog> m_data;

    SymptomLogManager *m_manager;

    QDateTime m_date;
    Q_PROPERTY(QDateTime date READ date WRITE setDate NOTIFY dateChanged FINAL)
};

#endif // SYMPTOMLOGMODEL_H
