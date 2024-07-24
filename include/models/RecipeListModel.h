#ifndef RECIPELISTMODEL_H
#define RECIPELISTMODEL_H

#include "Recipe.h"
#include <QAbstractListModel>
#include <QQmlEngine>

class RecipeListModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(int meal READ meal WRITE setMeal NOTIFY mealChanged FINAL)
public:

    enum RLMRoleTypes
    {
        FOODS = Qt::UserRole+1,
        NAME,
        UNITS,
        ID,
        RECIPE
    };

    RecipeListModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    Q_INVOKABLE void add(const QList<FoodServing> &foods, const QString &name, const double servings = 1);
    Q_INVOKABLE void add(const Recipe &recipe);
    Q_INVOKABLE void add(const QList<Recipe> &recipes);

    Q_INVOKABLE void clear();

    Q_INVOKABLE void search(const QString &query);

    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    Q_INVOKABLE static void cache(const FoodItem &item);

    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Q_INVOKABLE void loadData();
    Q_INVOKABLE void saveData();

    int meal() const;
    void setMeal(int newMeal);

signals:
    void mealChanged();
    void searchComplete();

protected:
    QHash<int, QByteArray> roleNames() const override;
private:
    QList<Recipe> m_data;

    int m_meal;
};

#endif // RECIPELISTMODEL_H
