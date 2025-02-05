#ifndef CARDIOMODEL_H
#define CARDIOMODEL_H

#include <QAbstractItemModel>

#include "Cardio.h"
#include "CardioManager.h"

class CardioModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    enum EMRoleTypes {
        NAME = Qt::UserRole + 1,
        TIME,
        CALS,
        IDX
    };

    explicit CardioModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    // Add data:
    Q_INVOKABLE void add(const Cardio &e, bool doSave = true);
    Q_INVOKABLE void add(const QList<Cardio> &e);
    Q_INVOKABLE void add(QString name, bool doSave = true);
    Q_INVOKABLE bool remove(int row);

    void clear();
    void save();

    Q_INVOKABLE void load();
    QDate date() const;
    void setDate(const QDate &newDate);

    CardioModel *fromJson(const QJsonArray &arr, QObject *parent);
    QJsonArray toJson() const;

    Q_INVOKABLE QList<Cardio> data() const;
    double calories() const;
    void resetCalories();

signals:
    void dateChanged();

    void caloriesChanged();

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<Cardio> m_data;

    double m_calories;
    CardioManager *m_manager;

    QDate m_date;
    Q_PROPERTY(QDate date READ date WRITE setDate NOTIFY dateChanged FINAL)
    Q_PROPERTY(double calories READ calories RESET resetCalories NOTIFY caloriesChanged FINAL)
};

#endif // CARDIOMODEL_H
