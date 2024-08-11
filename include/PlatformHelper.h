#ifndef PLATFORMHELPER_H
#define PLATFORMHELPER_H

#include <QObject>
#include <QQmlEngine>

class PlatformHelper : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit PlatformHelper(QObject *parent = nullptr);

    Q_INVOKABLE bool isWindows();

signals:
};

#endif // PLATFORMHELPER_H
