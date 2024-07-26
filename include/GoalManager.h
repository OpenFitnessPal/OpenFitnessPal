#ifndef GOALMANAGER_H
#define GOALMANAGER_H

#include <QObject>
#include <QQmlEngine>

class GoalManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit GoalManager(QObject *parent = nullptr);

    Q_INVOKABLE void setValue(const QString &key, const QVariant &value);

    Q_INVOKABLE QVariant getValue(const QString &key);
signals:
};

#endif // GOALMANAGER_H
