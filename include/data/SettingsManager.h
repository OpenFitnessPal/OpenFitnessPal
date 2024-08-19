#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <qcontainerfwd.h>
#include <qdir.h>

#include <QQmlEngine>

class SettingsManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    SettingsManager();

    enum SettingsError {
        Success,
        Failure,
        NoOp
    };

    Q_INVOKABLE SettingsError set(QString field, QVariant data) const;
    Q_INVOKABLE QVariantMap load() const;
    Q_INVOKABLE QVariant get(const QString &field) const;

    Q_INVOKABLE void rm(const QString &field) const;

    Q_INVOKABLE SettingsError mvDataDir(const QString &newPath);
    Q_INVOKABLE SettingsError mvCacheDir(const QString &newPath);

    Q_INVOKABLE void newDataDir(const QString &newPath);
    Q_INVOKABLE void newCacheDir(const QString &newPath);

    Q_INVOKABLE bool cacheExists(const QString &dir);
    Q_INVOKABLE bool dataExists(const QString &dir);

    Q_INVOKABLE void reloadCache();
private:
    QDir settingsDir;
};

#endif // SETTINGSMANAGER_H
