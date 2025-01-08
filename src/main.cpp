#include "GoalManager.h"
#include "MealNamesModel.h"
#include "SearchSettingsManager.h"
#include "WeightManager.h"

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

    SearchSettingsManager *searchSettings = new SearchSettingsManager(&app);
    engine.rootContext()->setContextProperty("searchSettings", searchSettings);

    GoalManager *goals = new GoalManager(&app);
    engine.rootContext()->setContextProperty("goalManager", goals);

    WeightManager *weight = new WeightManager(&app);
    engine.rootContext()->setContextProperty("weightManager", weight);

    engine.loadFromModule("OpenFitnessPal", "Main");

    return app.exec();
}
