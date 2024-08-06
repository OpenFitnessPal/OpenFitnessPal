#include "data/SettingsManager.h"
#include "DataManager.h"
#include <CacheManager.h>
#include <qdiriterator.h>
#include <qstandardpaths.h>

SettingsManager::SettingsManager()
{
    settingsDir = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    settingsDir.mkpath(".");
}

SettingsManager::SettingsError SettingsManager::set(QString field, QVariant data)
{
    QDir dir(settingsDir);

    QStringList split = field.split('/');
    QString fileName = split.last();
    split.pop_back();
    QString fileDir = split.join('/');

    if (!split.empty()) {
        bool ok = dir.mkpath(fileDir);

        if (!ok) {
            return Failure;
        }

        dir.cd(fileDir);
    }

    QFile file(dir.absoluteFilePath(fileName));
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        return Failure;
    }

    file.write(data.toByteArray());
    file.close();

    return Success;
}

QVariantMap SettingsManager::load()
{
    QVariantMap map{};

    QDirIterator iter(settingsDir, QDirIterator::IteratorFlag::Subdirectories);

    while (iter.hasNext()) {
        QFile f = iter.next();
        QString fileName = f.fileName();
        QString baseName = fileName.split('/').last();
        if (baseName.startsWith('.')) continue;

        f.open(QIODevice::ReadOnly | QIODevice::Text);
        QVariant var = f.readAll();

        map.insert(baseName, var);
        f.close();
    }

    return map;

}

QVariant SettingsManager::get(const QString &field)
{
    QVariant value{};

    QFile f(settingsDir.absoluteFilePath(field));
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return value;
    }

    value = f.readAll();

    f.close();

    return value;
}

SettingsManager::SettingsError SettingsManager::mvDataDir(const QString &newPath)
{
    DataManager::DataError err = DataManager::mv(newPath);

    switch (err) {
    case DataManager::Failure:
        return Failure;
    case DataManager::Success:
        return Success;
    default:
        return NoOp;
    }
}

SettingsManager::SettingsError SettingsManager::mvCacheDir(const QString &newPath)
{
    CacheManager::CacheResult err = CacheManager::mv(newPath);

    switch (err) {
    case CacheManager::Failure:
        return Failure;
    case CacheManager::Success:
        return Success;
    default:
        return NoOp;
    }

}
