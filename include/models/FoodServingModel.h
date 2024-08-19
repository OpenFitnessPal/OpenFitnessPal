#ifndef FOODSERVINGMODEL_H
#define FOODSERVINGMODEL_H

#include "FoodItem.h"
#include "OFPManager.h"
#include "SettingsManager.h"
#include <QAbstractListModel>
#include <QQmlEngine>

class FoodServingModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(int meal READ meal WRITE setMeal NOTIFY mealChanged FINAL)
    Q_PROPERTY(bool offlineSearch READ offlineSearch WRITE setOfflineSearch NOTIFY offlineSearchChanged FINAL)
    Q_PROPERTY(QList<FoodServing> foods READ foods)
public:

    enum FSMRoleTypes
    {
        ITEM = Qt::UserRole+1,
        SIZE,
        UNITS,
        ID,
        MEAL,
        SERVING
    };

    FoodServingModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    QList<FoodServing> foods() const;

    Q_INVOKABLE void add(const FoodItem &item, const ServingSize &size, const double units = 1);
    Q_INVOKABLE void add(const FoodServing &serving);
    Q_INVOKABLE void add(const QList<FoodServing> &serving);

    Q_INVOKABLE void clear();

    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    Q_INVOKABLE static void cache(const FoodItem &item);
    Q_INVOKABLE static void cache(const QList<FoodServing> &item);

    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Q_INVOKABLE void search(const QString &query);

    Q_INVOKABLE void loadData(QDate date);
    Q_INVOKABLE void saveData(QDate date);

    int meal() const;
    void setMeal(int newMeal);

    bool offlineSearch() const;
    void setOfflineSearch(bool newOfflineSearch);

signals:
    void mealChanged();
    void searchComplete();

    void offlineSearchChanged();

protected:
    QHash<int, QByteArray> roleNames() const override;
private:
    QList<FoodServing> m_data;

    int m_meal;
    bool m_offlineSearch;

    OFPManager *m_manager;

    SettingsManager m_settings;
};

#endif // FOODSERVINGMODEL_H
