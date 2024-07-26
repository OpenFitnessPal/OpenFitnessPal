// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>

#include "DataManager.h"
#include "CacheManager.h"
#include "GoalManager.h"
#include "Settings.h"
#include "autogen/environment.h"

#include <QQmlContext>
#include <BuildConfig.h>

int main(int argc, char *argv[])
{
#ifdef Q_OS_ANDROID
    qputenv("QT_SCALE_FACTOR", QByteArray::number(2));
#endif

    set_qt_environment();
    QGuiApplication app(argc, argv);
    app.setApplicationDisplayName(BuildConfig.APP_NAME);
    app.setApplicationName(BuildConfig.APP_NAME);
    app.setApplicationVersion(BuildConfig.versionString());
    app.setOrganizationName(BuildConfig.ORG_NAME);

    QQmlApplicationEngine engine;

    Settings settings;
    Recipe recipe;
    GoalManager manager;

    DataManager::init();
    CacheManager::init();

    engine.rootContext()->setContextProperty("settings", &settings);
    engine.rootContext()->setContextProperty("goalManager", &manager);
    engine.rootContext()->setContextProperty("blankRecipe", QVariant::fromValue(recipe));

    const QUrl url(mainQmlFile);
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url, &engine](QObject *obj, const QUrl &objUrl) mutable {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);

    engine.addImportPath(QCoreApplication::applicationDirPath() + "/qml");
    engine.addImportPath(":/");
    engine.load(url);

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
