#ifndef NUTRITIONMANAGER_H
#define NUTRITIONMANAGER_H

#include "NutrientUnion.h"
#include <QObject>
#include <QQmlEngine>

class NutritionManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit NutritionManager(QObject *parent = nullptr);

    Q_INVOKABLE NutrientUnion getDailyNutrients(QDate date);

signals:
};

#endif // NUTRITIONMANAGER_H
