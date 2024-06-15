#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <OFP/FoodItem.h>

#include <QDir>

class DataManager
{
public:
    static void init();

private:
    static QDir dataDir;
};

#endif // DATAMANAGER_H
