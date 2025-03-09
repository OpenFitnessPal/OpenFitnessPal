#ifndef WEIGHTMANAGER_H
#define WEIGHTMANAGER_H

#include "DataManager.h"

#include <QDir>
#include <QObject>
#include <QQmlEngine>

class WeightManager : public DataManager
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(int weight READ get WRITE set NOTIFY weightChanged FINAL)
public:
    WeightManager(QObject *parent = nullptr);

    Q_INVOKABLE bool set(const int weight);
    Q_INVOKABLE int get();

signals:
    void weightChanged();
};

#endif // WEIGHTMANAGER_H
