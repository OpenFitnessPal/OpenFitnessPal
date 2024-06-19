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

    Q_INIT_RESOURCE(breeze);


    QFile file(":/dark/stylesheet.qss");
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream stream(&file);
    a.setStyleSheet(stream.readAll());
    file.close();

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
