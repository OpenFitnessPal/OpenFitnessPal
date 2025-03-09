#ifndef FOODMANAGER_H
#define FOODMANAGER_H

#include "DataManager.h"

#include <FoodItem.h>

#include <QDir>
#include <QObject>
#include <QQmlEngine>

class FoodManager : public DataManager
{
    Q_OBJECT
    QML_ELEMENT

    int m_meal;
public:
    FoodManager(QObject *parent = nullptr);

    Q_INVOKABLE bool save(const QList<FoodServing> &foods);
    Q_INVOKABLE QList<FoodServing> load();

    int meal() const;
    void setMeal(int newMeal);

signals:
    void mealChanged();

private:
    Q_PROPERTY(int meal READ meal WRITE setMeal NOTIFY mealChanged FINAL REQUIRED)
};

#endif // FOODMANAGER_H
