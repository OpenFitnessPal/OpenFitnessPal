#include "../include/BackupManager.h"
#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QStandardPaths>
#include <QUrl>
#include <JlCompress.h>

BackupManager::BackupManager(QObject *parent)
    : QObject{parent}
{}

bool BackupManager::backup(const QUrl &url)
{
    QString name = url.toString();

#ifdef Q_OS_WINDOWS
    name.replace("file:///", "");
#else
    name.replace("file://", "");
#endif

    QDir dir = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);

    return JlCompress::compressDir(name, dir.absolutePath(), true);
}

bool BackupManager::restore(const QUrl &url)
{
    QString name = url.toString();

#ifdef Q_OS_WINDOWS
    name.replace("file:///", "");
#else
    name.replace("file://", "");
#endif

    // completely wipe dir
    QDir dir = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    dir.removeRecursively();
    dir.mkpath(".");

    return !JlCompress::extractDir(name, dir.absolutePath()).empty();
}
