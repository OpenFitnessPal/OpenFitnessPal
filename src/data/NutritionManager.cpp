#include "data/NutritionManager.h"

#include <QDirIterator>
#include <QJsonArray>
#include <QJsonDocument>
#include <QStandardPaths>

NutritionManager::NutritionManager(QObject *parent)
    : QObject(parent)
{
    resetDate();
    m_dir = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
}

QDate NutritionManager::date() const
{
    return m_date;
}

void NutritionManager::setDate(const QDate &newDate)
{
    if (m_date == newDate)
        return;
    m_date = newDate;
    emit dateChanged();
}

void NutritionManager::resetDate()
{
    setDate(QDate::currentDate());
}

NutrientUnion NutritionManager::load(int daysBack)
{
    int totalDays = 0;
    NutrientUnion total;
    for (int i = 0; i < daysBack; ++i) {
        NutrientUnion today;
        int numMeals = 0;

        QDir dir(m_dir);
        if (!mkDate(i, dir)) continue;

        if (!dir.cd("meals")) continue;

        QDirIterator iter(dir);
        while (iter.hasNext()) {
            QFile f = iter.next();
            QString baseName = iter.fileInfo().baseName();

            if (baseName == "") continue;

            ++numMeals;

            f.open(QIODevice::ReadOnly | QIODevice::Text);

            QByteArray data = f.readAll();
            QJsonDocument doc = QJsonDocument::fromJson(data);

            QJsonArray array = doc.array();

            for (QJsonValueRef ref : array) {
                QJsonObject obj = ref.toObject();
                FoodServing s = FoodServing::fromJson(obj);
                today += s.nutrients();
            }

            f.close();
        }

        total += today;
        if (numMeals > 0) ++totalDays;
    }

    return total / totalDays;
}

bool NutritionManager::mkDate(int daysBack, QDir &dir) {
    QDate newDate = m_date.addDays(-daysBack);
    QString dateString = newDate.toString("MM-dd-yyyy");

    if (!dir.exists(dateString)) {
        return false;
    }

    if (!dir.mkpath(dateString)) {
        return false;
    }

    dir.cd(dateString);
    return true;
}
