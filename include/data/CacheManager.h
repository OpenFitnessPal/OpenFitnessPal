#ifndef CACHEMANAGER_H
#define CACHEMANAGER_H

#include <FoodItem.h>
#include <QDir>

class CacheManager : public QObject
{
public:
    CacheManager(QObject *parent = nullptr);
    void load();

    Q_INVOKABLE bool cache(const FoodItem &item);
    Q_INVOKABLE QList<FoodItem> search(const QString &pattern) const;

private:
    QList<FoodItem> m_cachedFoods;

    QDir m_dir;
};

#endif // CACHEMANAGER_H
