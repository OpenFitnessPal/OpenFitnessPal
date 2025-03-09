#ifndef NUTRITIONMANAGER_H
#define NUTRITIONMANAGER_H


#include "DataManager.h"

#include <FoodItem.h>

#include <QDir>
#include <QObject>
#include <QQmlEngine>

class NutritionManager : public DataManager
{
    Q_OBJECT
    QML_ELEMENT

    NutrientUnion m_today;
    NutrientUnion m_week;
    QList<NutrientUnion> m_weekList;

    Q_PROPERTY(NutrientUnion today READ today NOTIFY todayChanged FINAL)
    Q_PROPERTY(NutrientUnion week READ week NOTIFY weekChanged FINAL)
    Q_PROPERTY(QList<NutrientUnion> weekList READ weekList NOTIFY weekListChanged FINAL)

public:
    NutritionManager(QObject *parent = nullptr);

    Q_INVOKABLE NutrientUnion load(int daysBack);
    Q_INVOKABLE QList<NutrientUnion> list(int daysBack);

    NutrientUnion today() const;
    NutrientUnion week() const;
    QList<NutrientUnion> weekList() const;

    Q_INVOKABLE void updateNutrients();

signals:
    void todayChanged();

    void weekChanged();

    void weekListChanged();

private:
    bool mkDate(int daysBack, QDir &dir);
};

#endif // NUTRITIONMANAGER_H
