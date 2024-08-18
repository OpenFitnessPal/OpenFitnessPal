#ifndef NUTRIENTMODEL_H
#define NUTRIENTMODEL_H

#include "GoalManager.h"
#include "NutritionManager.h"
#include "SettingsManager.h"
#include <QDate>
#include <QAbstractListModel>
#include <QObject>
#include <QQmlEngine>

typedef struct Nutrient {
    QString displayName;
    QString name;
} Nutrient;

class NutrientModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QDate date READ date WRITE setDate FINAL)
public:
    enum NMRoleTypes
    {
        NAME = Qt::UserRole+1,
        DNAME,
        GOAL,
        VALUE,
        FILTER,
        ID
    };

    NutrientModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    Q_INVOKABLE void add(const Nutrient &n);
    Q_INVOKABLE void add(QString name = "", QString displayName = "");
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    Q_INVOKABLE void remove(QString name);

    Q_INVOKABLE void clear();

    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Q_INVOKABLE void loadData();
    Q_INVOKABLE void loadFilterData();
    Q_INVOKABLE void loadUnfilteredData();

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    QDate date() const;
    void setDate(const QDate &newDate);

protected:
    QHash<int, QByteArray> roleNames() const override;
private:
    QList<Nutrient> m_data;

    QDate m_date;

    GoalManager m_goals;
    NutritionManager m_nutrition;
    SettingsManager m_settings;

    QList<Nutrient> m_nutrients;
};

#endif // NUTRIENTMODEL_H
