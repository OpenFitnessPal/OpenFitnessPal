#include "include/data/CacheManager.h"

#include <QFile>
#include <QDir>
#include <QDirIterator>
#include <QStandardPaths>

#include <QJsonDocument>

QDir CacheManager::dir{};
QList<FoodItem> CacheManager::cachedFoods{};

void CacheManager::init()
{
    QString dirString = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
    dir = dirString;

    bool ok = dir.mkpath(".");

    if (!ok) {
        qCritical() << "Failed to create food cache directory, exiting.";
        std::exit(127);
    }

    load();
}

void CacheManager::load()
{
    cachedFoods.clear();

    QDirIterator cacheIter(dir.absolutePath(), {"*.json"}, QDir::Files);

    while (cacheIter.hasNext()) {
        QFile f(cacheIter.next());
        f.open(QIODevice::ReadOnly | QIODevice::Text);
        QByteArray json = f.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(json);

        FoodItem item(doc.object());
        cachedFoods.append(item);
    }

}

bool CacheManager::cache(const FoodItem &item)
{
    QJsonObject obj = item.toJson();
    QJsonDocument doc{obj};

    QFile file(dir.absoluteFilePath(item.id() + ".json"));
    if (file.exists()) {
        if (!file.open(QIODevice::ReadWrite)) {
            return false;
        }

        QByteArray content = file.readAll();
        if (content == doc.toJson()) {
            return true;
        }
    } else if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        return false;
    }

    if (cachedFoods.contains(item)) {
        cachedFoods.removeOne(item);
    }

    cachedFoods.append(item);

    file.write(doc.toJson());
    file.close();

    return true;
}

QList<FoodItem> CacheManager::search(const QString &pattern)
{
    QRegularExpression regex(".*" + pattern + ".*", QRegularExpression::PatternOption::CaseInsensitiveOption);

    QList<FoodItem> results{};

    for (const FoodItem &item : cachedFoods) {
        if (item.name().contains(regex)) {
            results.append(item);
        }
    }

    return results;
}
