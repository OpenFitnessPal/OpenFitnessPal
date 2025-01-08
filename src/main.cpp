#include "MealNamesModel.h"
#include "CacheManager.h"

#include <BuildConfig.h>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QQuickStyle>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    app.setOrganizationName(BuildConfig.ORG_NAME);
    app.setApplicationName(BuildConfig.APP_NAME);
    app.setApplicationVersion(BuildConfig.versionString());

    QQuickStyle::setStyle("Universal");

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    MealNamesModel *mealNames = new MealNamesModel(&app);
    engine.rootContext()->setContextProperty("mealNamesModel", mealNames);

    CacheManager *cache = new CacheManager(&app);

    engine.loadFromModule("OpenFitnessPal", "Main");

    return app.exec();
}
