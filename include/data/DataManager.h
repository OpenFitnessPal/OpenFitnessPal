#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <OFP/FoodItem.h>

#include <QDir>

typedef std::tuple<FoodItem, ServingSize, double> FoodServing;

class DataManager
{
public:
    static void init();

    enum DataError {
        Success,
        Failure,
        NoOp
    };

    static DataError saveFood(int meal, QDate date, const FoodItem &item, const ServingSize &size, const double units);
    static QList<FoodServing> loadFoods(int meal, QDate date);

private:
    static QDir dataDir;
};

#endif // DATAMANAGER_H
