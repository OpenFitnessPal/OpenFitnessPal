#ifndef CACHEMANAGER_H
#define CACHEMANAGER_H

#include "FoodItem.h"
#include <QDir>

class CacheManager
{
public:
    static void init();

    enum CacheResult {
        Success,
        Failure,
        NoOp
    };

    static CacheResult cacheFoodItem(const FoodItem &item);

    static QList<FoodItem> search(const QString &pattern);

    static FoodItem itemById(const QString &id);

private:
    static QList<FoodItem> cachedFoods;

    static QDir cacheDir;
};

#endif // CACHEMANAGER_H
