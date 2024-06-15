#include "data/DataManager.h"

#include <QFile>
#include <QDir>
#include <QStandardPaths>

#include <QMessageBox>

void DataManager::init()
{
    QDir dataDir = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    bool ok = dataDir.mkdir("openfitnesspal");

    if (!ok) {
        QMessageBox::critical(nullptr, "mkdir failed", "Failed to make data directory. Check permissions on your local data directory.", QMessageBox::StandardButton::Ok);
        std::exit(127);
    }

    dataDir.cd("openfitnesspal");
}
