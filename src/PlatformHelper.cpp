#include "PlatformHelper.h"

#include <BuildConfig.h>

PlatformHelper::PlatformHelper(QObject *parent)
    : QObject{parent}
{}

bool PlatformHelper::isWindows()
{
    return BuildConfig.BUILD_PLATFORM == "win32";
}
