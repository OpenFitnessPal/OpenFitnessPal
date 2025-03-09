#ifndef RecipeModel_H
#define RecipeModel_H

#include "Recipe.h"
#include "RecipeManager.h"
#include <QAbstractListModel>
#include <QQmlEngine>

class RecipeModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int meal READ meal WRITE setMeal NOTIFY mealChanged FINAL)
public:

    enum RLMRoleTypes
    {
        FOODS = Qt::UserRole+1,
        NAME,
        UNITS,
        ID,
        RECIPE,
        NUTRIENTS
    };

    RecipeModel(RecipeManager *manager, bool editable, QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    Q_INVOKABLE void add(const QList<FoodServing> &foods, const QString &name, const double servings = 1, bool doSave = true);
    Q_INVOKABLE void add(const Recipe &recipe);
    Q_INVOKABLE void add(const QList<Recipe> &recipes);
    Q_INVOKABLE void add(const QString &name);

    Q_INVOKABLE void clear();

    Q_INVOKABLE void remove(int idx);

    Q_INVOKABLE void search(const QString &query);

    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Q_INVOKABLE void load();

    int meal() const;
    void setMeal(int newMeal);

signals:
    void mealChanged();
    void searchComplete();

protected:
    QHash<int, QByteArray> roleNames() const override;
private:
    QList<Recipe> m_data;
    bool m_editable;

    int m_meal;

    RecipeManager *m_manager;
};

#endif // RecipeModel_H
