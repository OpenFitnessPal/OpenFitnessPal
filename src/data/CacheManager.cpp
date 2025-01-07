#include "include/data/CacheManager.h"

#include <QFile>
#include <QDir>
#include <QDirIterator>
#include <QStandardPaths>

#include <QJsonDocument>

CacheManager::CacheManager(QObject *parent)
    : QObject(parent)
{
    QString dir = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
    m_dir = dir;

    bool ok = m_dir.mkpath(".");

    if (!ok) {
        qCritical() << "Failed to create food cache directory, exiting.";
        std::exit(127);
    }

    load();
}

void CacheManager::load()
{
    m_cachedFoods.clear();

    QDirIterator cacheIter(m_dir.absolutePath(), {"*.json"}, QDir::Files);

    while (cacheIter.hasNext()) {
        QFile f(cacheIter.next());
        f.open(QIODevice::ReadOnly | QIODevice::Text);
        QByteArray json = f.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(json);

        FoodItem item(doc.object());
        m_cachedFoods.append(item);
    }

}

bool CacheManager::cache(const FoodItem &item)
{
    QJsonObject obj = item.toJson();
    QJsonDocument doc{obj};

    QFile file(m_dir.absoluteFilePath(item.id() + ".json"));
    if (file.exists()) {
        if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
            return false;
        }

        QByteArray content = file.readAll();
        if (content == doc.toJson()) {
            return true;
        }
    } else if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        return false;
    }

    if (m_cachedFoods.contains(item)) {
        m_cachedFoods.removeOne(item);
    }

    m_cachedFoods.append(item);

    file.write(doc.toJson());
    file.close();

    return true;
}

QList<FoodItem> CacheManager::search(const QString &pattern) const
{
    QRegularExpression regex(".*" + pattern + ".*", QRegularExpression::PatternOption::CaseInsensitiveOption);

    QList<FoodItem> results{};

    for (const FoodItem &item : m_cachedFoods) {
        if (item.name().contains(regex)) {
            results.append(item);
        }
    }

    return results;
}
