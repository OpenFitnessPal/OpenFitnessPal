#ifndef BACKUPMANAGER_H
#define BACKUPMANAGER_H

#include <QObject>

class BackupManager : public QObject
{
    Q_OBJECT
public:
    explicit BackupManager(QObject *parent = nullptr);

    Q_INVOKABLE bool backup(const QUrl &url);
    Q_INVOKABLE bool restore(const QString &file);

signals:
};

#endif // BACKUPMANAGER_H
