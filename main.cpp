#include "MainWindow.h"

#include <QApplication>
#include <QSettings>

#include "data/CacheManager.h"
#include "data/DataManager.h"

#include "Settings.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("OpenFitnessPal");
    a.setApplicationName("OpenFitnessPal");
    a.setApplicationVersion("0.0.1");

    CacheManager::init();
    DataManager::init();

    MainWindow w;
    w.show();

    if (Settings::FirstRun.value().toBool()) {
        Settings::FirstRun.setValue(false);

        // SetupWizard *wizard = new SetupWizard(&w);
        // wizard->show();
    }
    return a.exec();
}
