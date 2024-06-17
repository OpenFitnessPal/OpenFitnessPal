#include "data/CacheManager.h"

#include <OFP/FoodItem.h>

#include <QFile>
#include <QDir>
#include <QDirIterator>
#include <QStandardPaths>

#include <QJsonDocument>

#include <QMessageBox>

QList<FoodItem> CacheManager::cachedFoods{};

QDir CacheManager::cacheDir{};

void CacheManager::init()
{
    cacheDir = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
    bool ok = cacheDir.mkpath("foods");

    if (!ok) {
        QMessageBox::critical(nullptr, "mkpath failed", "Failed to make cache directory. Check permissions on your local cache directory.", QMessageBox::StandardButton::Ok);
        std::exit(127);
    }

    cacheDir.cd("foods");

    QDirIterator cacheIter(cacheDir.absolutePath(), {"*.json"}, QDir::Files);

    while (cacheIter.hasNext()) {
        QFile f(cacheIter.next());
        f.open(QIODevice::ReadOnly | QIODevice::Text);
        QByteArray json = f.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(json);

        FoodItem item(doc.object());
        cachedFoods.append(item);
    }
}

CacheManager::CacheResult CacheManager::cacheFoodItem(const FoodItem &item)
{
    QJsonObject obj = item.toJson();
    QJsonDocument doc{obj};

    QFile file(cacheDir.absoluteFilePath(item.id() + ".json"));
    if (file.exists()) {
        if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
            goto error;
        }

        QByteArray content = file.readAll();
        if (content == doc.toJson()) {
            return NoOp;
        }
    } else if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        goto error;
    }

    if (cachedFoods.contains(item)) {
        cachedFoods.removeOne(item);
    }

    cachedFoods.append(item);

    file.write(doc.toJson());
    file.close();

    return Success;

error:
    QMessageBox::critical(nullptr, "Failed to Cache Food Item", "Couldn't cache food item. Check to ensure local cache directory exists and is writable.", QMessageBox::StandardButton::Ok);
    return Failure;
}

QList<FoodItem> CacheManager::search(const QString &pattern)
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QRegExp regex(".*" + pattern + ".*", Qt::CaseInsensitive);
#else
    QRegularExpression regex(".*" + pattern + ".*", QRegularExpression::PatternOption::CaseInsensitiveOption);
#endif

    QList<FoodItem> results{};

    for (const FoodItem &item : cachedFoods) {
        if (item.name().contains(regex)) {
            results.append(item);
        }
    }

    return results;
}

FoodItem CacheManager::itemById(const QString &id)
{
    for (const FoodItem &food : cachedFoods) {
        if (food.id() == id) {
            return food;
        }
    }

    return FoodItem{};
}
