#include "data/NutritionManager.h"

#include <QDirIterator>
#include <QJsonArray>
#include <QJsonDocument>
#include <QStandardPaths>

NutrientUnion NutritionManager::today() const
{
    return m_today;
}

NutrientUnion NutritionManager::week() const
{
    return m_week;
}

QList<NutrientUnion> NutritionManager::weekList() const
{
    return m_weekList;
}

void NutritionManager::updateNutrients()
{
    m_today = load(1);
    m_week = load(7);
    m_weekList = list(7);

    emit todayChanged();
    emit weekChanged();
    emit weekListChanged();
}

NutritionManager::NutritionManager(QObject *parent)
    : DataManager(parent)
{
    m_useDate = true;
    updateNutrients();
}

NutrientUnion NutritionManager::load(int daysBack)
{
    auto weekList = list(daysBack);

    NutrientUnion total;
    int numDays = 0;
    for (const NutrientUnion &n : weekList) {
        total += n;
        // ?????
        if (!(n == NutrientUnion{})) {
            numDays++;
        }
    }

    return total / numDays;
}

QList<NutrientUnion> NutritionManager::list(int daysBack)
{
    int totalDays = 0;
    QList<NutrientUnion> days;
    for (int i = daysBack - 1; i > -1; --i) {
        NutrientUnion today;
        int numMeals = 0;

        QDir dir(m_dir);

        if (!mkDate(i, dir)) goto cont;

        if (!dir.cd("meals")) goto cont;

        {
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

                for (QJsonValueRef ref : (array)) {
                    QJsonObject obj = ref.toObject();
                    FoodServing s = FoodServing::fromJson(obj);
                    today += s.nutrients();
                }

                f.close();
            }
        }

    cont:
        days << today;
    }

    return days;
}

bool NutritionManager::mkDate(int daysBack, QDir &dir) {
    QDateTime newDate = m_date.addDays(-daysBack);
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
