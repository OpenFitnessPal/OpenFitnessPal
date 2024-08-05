#include "data/SettingsManager.h"
#include <qdiriterator.h>
#include <qstandardpaths.h>

SettingsManager::SettingsManager()
{
    settingsDir = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    bool ok = settingsDir.mkpath("settings");

    if (!ok) {
        // QMessageBox::critical(nullptr, "mkpath failed", "Failed to make data directory. Check permissions on your local data directory.", QMessageBox::StandardButton::Ok);
        std::exit(127);
    }
}

SettingsManager::SettingsError SettingsManager::set(QString field, QVariant data)
{
    QDir dir(settingsDir);
    dir.cd("settings");

    QStringList split = field.split('/');
    QString fileName = split.last();
    split.pop_back();
    QString fileDir = split.join('/');

    if (!split.empty()) {
        bool ok = dir.mkpath(fileDir);

        if (!ok) {
            // QMessageBox::critical(nullptr, "mkdir failed", "Failed to make personal info directory. Check permissions on your local data directory.", QMessageBox::StandardButton::Ok);
            return Failure;
        }

        dir.cd(fileDir);
    }

    QFile file(dir.absoluteFilePath(fileName));
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        // QMessageBox::critical(nullptr, "Write failed", "Failed to save personal info. Check permissions on your local data directory.", QMessageBox::StandardButton::Ok);
        return Failure;
    }

    file.write(data.toByteArray());
    file.close();

    return Success;
}

QVariantMap SettingsManager::load()
{
    QVariantMap map{};
    QDir dir(settingsDir);
    dir.cd("settings");

    QDirIterator iter(dir, QDirIterator::IteratorFlag::Subdirectories);

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
    QDir dir(settingsDir);
    dir.cd("settings");

    QFile f(dir.absoluteFilePath(field));
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return value;
    }

    value = f.readAll();

    f.close();

    return value;
}

