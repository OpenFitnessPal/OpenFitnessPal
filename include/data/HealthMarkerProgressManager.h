#ifndef HEALTHMARKERPROGRESSMANAGER_H
#define HEALTHMARKERPROGRESSMANAGER_H

#include "DataManager.h"
#include "HealthMarkerManager.h"

#include <FoodItem.h>

#include <QDir>
#include <QObject>
#include <QQmlEngine>

typedef QList<HealthMarker> MarkerList;

class HealthMarkerProgressManager : public DataManager
{
    Q_OBJECT
    QML_ELEMENT

public:
    HealthMarkerProgressManager(QObject *parent = nullptr);

    Q_INVOKABLE QList<MarkerList> load(int daysBack);

private:
    bool mkDate(int daysBack, QDir &dir);
};

#endif // HEALTHMARKERPROGRESSMANAGER_H
