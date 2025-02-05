#include "GoalManager.h"
#include "MealNamesModel.h"
#include "NutrientModel.h"
#include "SearchSettingsManager.h"
#include "WeightManager.h"

#include <BuildConfig.h>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <CacheManager.h>
#include <QIcon>
#include <QQuickStyle>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    app.setOrganizationName(BuildConfig.ORG_NAME);
    app.setApplicationName(BuildConfig.APP_NAME);
    app.setApplicationVersion(BuildConfig.versionString());

    app.setWindowIcon(QIcon(":/OpenFitnessPal"));

    QQuickStyle::setStyle("Universal");

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    CacheManager::init();

    MealNamesModel *mealNames = new MealNamesModel(&app);
    engine.rootContext()->setContextProperty("mealNamesModel", mealNames);

    SearchSettingsManager *searchSettings = new SearchSettingsManager(&app);
    engine.rootContext()->setContextProperty("searchSettings", searchSettings);

    GoalManager *goals = new GoalManager(&app);
    engine.rootContext()->setContextProperty("goalManager", goals);

    WeightManager *weight = new WeightManager(&app);
    engine.rootContext()->setContextProperty("weightManager", weight);

    NutrientModel *micros = new NutrientModel(false, true, &app);
    engine.rootContext()->setContextProperty("microsModel", micros);

    NutrientModel *macros = new NutrientModel(true, false, &app);
    engine.rootContext()->setContextProperty("macrosModel", macros);

    NutrientModel *all = new NutrientModel(true, true, &app);
    engine.rootContext()->setContextProperty("nutrientsModel", all);

    engine.loadFromModule("OpenFitnessPal", "Main");

    return app.exec();
}
