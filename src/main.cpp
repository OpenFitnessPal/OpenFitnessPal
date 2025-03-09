#include "DateManager.h"
#include "GoalManager.h"
#include "HealthMarkerModel.h"
#include "MealNamesModel.h"
#include "NutrientModel.h"
#include "NutritionManager.h"
#include "RecipeManager.h"
#include "RecipeModel.h"
#include "SearchSettingsManager.h"
#include "WeightManager.h"

#include <BuildConfig.h>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <CacheManager.h>
#include <QIcon>
#include <QQuickStyle>
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

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

    // I kind of hate how many of these we have but idc
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

    NutritionManager *nutrition = new NutritionManager(&app);
    engine.rootContext()->setContextProperty("nutritionManager", nutrition);

    DateManager *date = new DateManager(&app);
    engine.rootContext()->setContextProperty("dateManager", date);

    /**
     * RECIPES
     */
    RecipeManager *recipeManager = new RecipeManager(&app);

    RecipeModel *recipeEditModel = new RecipeModel(recipeManager, &app);
    RecipeModel *recipeSearchModel = new RecipeModel(recipeManager, &app);

    engine.rootContext()->setContextProperty("recipeSearchModel", recipeSearchModel);
    engine.rootContext()->setContextProperty("recipeEditModel", recipeEditModel);

    /**
     * Health Markers
     */

    HealthMarkerModel *healthMarkers = new HealthMarkerModel(&app);

    engine.rootContext()->setContextProperty("healthMarkerModel", healthMarkers);

    QObject::connect(date, &DateManager::dateChanged, nutrition, [nutrition, weight, date, goals, healthMarkers] () {
        nutrition->setDate(date->date());
        nutrition->updateNutrients();

        weight->setDate(date->date());
        emit weight->weightChanged();

        goals->setDate(date->date());
        goals->updateFields();

        healthMarkers->setDate(date->date());
    });

    engine.loadFromModule("OpenFitnessPal", "Main");

    return app.exec();
}
