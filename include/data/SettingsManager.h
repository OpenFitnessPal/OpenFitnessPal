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

    Q_INVOKABLE SettingsError set(QString field, QVariant data);
    Q_INVOKABLE QVariantMap load();
    Q_INVOKABLE QVariant get(const QString &field);

private:
    QDir settingsDir;
};

#endif // SETTINGSMANAGER_H
