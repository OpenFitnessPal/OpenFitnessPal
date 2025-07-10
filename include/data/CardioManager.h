#ifndef CardioManager_H
#define CardioManager_H

#include "DataManager.h"

#include <QObject>
#include <QDateTime>

#include <Cardio.h>
#include <QDir>

class CardioManager : public DataManager
{
    Q_OBJECT
public:
    CardioManager(QObject *parent);

    Q_INVOKABLE QList<Cardio> load();
    Q_INVOKABLE bool save(const QList<Cardio> &exercises);
};

#endif // CardioManager_H
