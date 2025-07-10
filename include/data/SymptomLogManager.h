#ifndef SYMPTOMLOGMANAGER_H
#define SYMPTOMLOGMANAGER_H

#include "SymptomLog.h"
#include <DataManager.h>

class SymptomLogManager : public DataManager
{
    Q_OBJECT
public:
    explicit SymptomLogManager(QObject *parent = nullptr);

    Q_INVOKABLE QList<SymptomLog> load();
    Q_INVOKABLE bool save(const QList<SymptomLog> &symptoms);
};

#endif // SYMPTOMLOGMANAGER_H
