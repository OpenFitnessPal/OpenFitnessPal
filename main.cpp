#include "MainWindow.h"
#include "setup/SetupWizard.h"

#include <QApplication>
#include <QSettings>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("OpenFitnessPal");
    a.setApplicationName("OpenFitnessPal");
    a.setApplicationVersion("0.0.1");

    MainWindow w;
    w.show();

    QSettings settings(&a);
    if (true) {//!settings.value("firstRun", false).toBool()) {
        settings.setValue("firstRun", true);

        SetupWizard *wizard = new SetupWizard(&w);
        wizard->showMaximized();
    }
    return a.exec();
}
