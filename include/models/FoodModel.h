#ifndef FOODMODEL_H
#define FOODMODEL_H

#include "FoodItem.h"
#include "FoodManager.h"
#include "OFPManager.h"
#include "SearchSettingsManager.h"
#include <QAbstractListModel>
#include <QQmlEngine>

class FoodModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(int meal READ meal WRITE setMeal NOTIFY mealChanged FINAL)
    Q_PROPERTY(bool offlineSearch READ offlineSearch WRITE setOfflineSearch NOTIFY offlineSearchChanged FINAL)
    Q_PROPERTY(QList<FoodServing> foods READ foods)

    Q_PROPERTY(SearchSettingsManager *settings READ settings WRITE setSettings NOTIFY settingsChanged FINAL)
    Q_PROPERTY(QDateTime date READ date WRITE setDate NOTIFY dateChanged FINAL)

public:

    enum FSMRoleTypes
    {
        ITEM = Qt::UserRole+1,
        SIZE,
        SIZEIDX,
        UNITS,
        ID,
        MEAL,
        SERVING,
        NAME
    };

    FoodModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    QList<FoodServing> foods() const;

    Q_INVOKABLE void add(const FoodItem &item, const ServingSize &size, const double units = 1);
    Q_INVOKABLE void add(const FoodItem &item);
    Q_INVOKABLE void add(const FoodServing &serving);
    Q_INVOKABLE void add(const QList<FoodServing> &serving);

    Q_INVOKABLE void clear();

    Q_INVOKABLE void remove(int index);
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    Q_INVOKABLE static void cache(const FoodItem &item);
    Q_INVOKABLE static void cache(const QList<FoodServing> &item);

    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Q_INVOKABLE void search(const QString &query);

    Q_INVOKABLE void load();
    Q_INVOKABLE void save();

    int meal() const;
    void setMeal(int newMeal);

    bool offlineSearch() const;
    void setOfflineSearch(bool newOfflineSearch);

    SearchSettingsManager *settings() const;
    void setSettings(SearchSettingsManager *newSettings);

    QDateTime date() const;
    void setDate(const QDateTime &newDate);

    double calories() const;
    void resetCalories();

    NutrientUnion nutrients() const;
    void resetNutrients();

signals:
    void mealChanged();
    void searchComplete();

    void offlineSearchChanged();

    void settingsChanged();

    void dateChanged();

    void dataChanged();

    void caloriesChanged();

    void nutrientsChanged();

protected:
    QHash<int, QByteArray> roleNames() const override;
private:
    QList<FoodServing> m_data;

    int m_meal;
    bool m_offlineSearch;
    QDateTime m_date;

    double m_calories;
    NutrientUnion m_nutrients;

    OFPManager *m_ofp;
    FoodManager *m_food;

    SearchSettingsManager *m_settings;
    Q_PROPERTY(double calories READ calories NOTIFY caloriesChanged FINAL)
    Q_PROPERTY(NutrientUnion nutrients READ nutrients RESET resetNutrients NOTIFY nutrientsChanged FINAL)
};

#endif // FOODMODEL_H
