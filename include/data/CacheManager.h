#ifndef CACHEMANAGER_H
#define CACHEMANAGER_H

#include <FoodItem.h>
#include <QDir>

class CacheManager : public QObject
{
public:
    static void init();
    static void load();

    static bool cache(const FoodItem &item);
    static QList<FoodItem> search(const QString &pattern);

private:
    static QList<FoodItem> cachedFoods;

    static QDir dir;
};

#endif // CACHEMANAGER_H
