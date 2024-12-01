// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>

#include "DataManager.h"
#include "CacheManager.h"
#include "GoalManager.h"
#include "PlatformHelper.h"
#include "NutritionManager.h"
#include "SettingsManager.h"

#include <QQmlContext>
#include <BuildConfig.h>

int main(int argc, char *argv[])
{
#ifdef Q_OS_ANDROID
    qputenv("QT_SCALE_FACTOR", QByteArray::number(2));
#endif

    QGuiApplication app(argc, argv);
    app.setApplicationDisplayName(BuildConfig.APP_NAME);
    app.setApplicationName(BuildConfig.APP_NAME);
    app.setApplicationVersion(BuildConfig.versionString());
    app.setOrganizationName(BuildConfig.ORG_NAME);

    PlatformHelper platform;
    Recipe recipe;
    GoalManager manager;
    NutritionManager nutrition;
    SettingsManager settings;

    DataManager::init();
    CacheManager::init();

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("settings", &settings);
    engine.rootContext()->setContextProperty("goalManager", &manager);
    engine.rootContext()->setContextProperty("nutritionManager", &nutrition);
    engine.rootContext()->setContextProperty("platform", &platform);
    engine.rootContext()->setContextProperty("blankRecipe", QVariant::fromValue(recipe));

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.loadFromModule("OpenFitnessPal", "App");

    return app.exec();
}
