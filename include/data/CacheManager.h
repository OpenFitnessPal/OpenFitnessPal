#ifndef CACHEMANAGER_H
#define CACHEMANAGER_H

#include "FoodItem.h"
#include <QDir>

class CacheManager
{
public:
    static void init();
    static void reload();

    enum CacheResult {
        Success,
        Failure,
        NoOp
    };

    static CacheResult cacheFoodItem(const FoodItem &item);

    static QList<FoodItem> search(const QString &pattern);

    static FoodItem itemById(const QString &id);

    static CacheResult mv(const QString &newPath);
    static void newPath(const QString &newPath);

private:
    static QList<FoodItem> cachedFoods;

    static QDir cacheDir;
};

#endif // CACHEMANAGER_H
