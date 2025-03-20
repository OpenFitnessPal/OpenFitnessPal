#include "../include/BackupManager.h"
#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QStandardPaths>
#include <QUrl>
#include <JlCompress.h>
#include <QFileInfo>
#include <QFileDialog>
#include <QBuffer>

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

bool BackupManager::restore(const QString &file)
{
    QString name = file;

#ifdef Q_OS_WINDOWS
    name.replace("file:///", "");
#else
    name.replace("file://", "");
#endif

    // completely wipe dir
    QDir dir = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    dir.removeRecursively();
    dir.mkpath(".");

    QFile f(name);
    if (!f.open(QIODevice::ReadOnly)) {
        qCritical() << "Failed to read file" << name;
        return false;
    } else {
        qInfo() << "Successfully read:" << name;
        QByteArray data = f.readAll();

        QBuffer buffer(&data);
        buffer.open(QIODevice::ReadOnly);

        QuaZip zip(&buffer);

        QStringList lst = JlCompress::extractDir(zip, dir.absolutePath());
        // qDebug() << "Extracted" << lst;

        f.close();
        return lst.empty();
    }
}
