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

    Q_INVOKABLE QString defaultDataDir();
    Q_INVOKABLE QString defaultCacheDir();

signals:
};

#endif // PLATFORMHELPER_H
