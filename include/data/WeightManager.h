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

    int m_weight = -1;
public:
    WeightManager(QObject *parent = nullptr);

    Q_INVOKABLE bool set(const int weight);
    Q_INVOKABLE int get(bool force = false);

public slots:
    void update();

signals:
    void weightChanged();
};

#endif // WEIGHTMANAGER_H
