#include "PlatformHelper.h"

#include <QStandardPaths>
#include <BuildConfig.h>

PlatformHelper::PlatformHelper(QObject *parent)
    : QObject{parent}
{}

bool PlatformHelper::isWindows()
{
    return BuildConfig.BUILD_PLATFORM == "win32";
}

QString PlatformHelper::defaultDataDir()
{
    return QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
}

QString PlatformHelper::defaultCacheDir()
{
    return QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
}
