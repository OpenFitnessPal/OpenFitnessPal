#include "data/HealthMarkerProgressManager.h"

#include <QDirIterator>
#include <QJsonArray>
#include <QJsonDocument>
#include <QStandardPaths>

HealthMarkerProgressManager::HealthMarkerProgressManager(QObject *parent)
    : DataManager(parent)
{
    m_useDate = true;
}

QList<MarkerList> HealthMarkerProgressManager::load(int daysBack)
{
    int totalDays = 0;
    QList<MarkerList> days;
    MarkerList prev;

    for (int i = daysBack - 1; i > -1; --i) {
        MarkerList list;

        QDir dir(m_dir);

        if (!mkDate(i, dir)) goto cont;

        {
            QFile f(dir.absoluteFilePath("health.json"));

            if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
                list = prev;
                goto cont;
            }

            QByteArray data = f.readAll();
            QJsonDocument doc = QJsonDocument::fromJson(data);

            QJsonArray array = doc.array();

            for (QJsonValueConstRef ref : std::as_const(array)) {
                QJsonObject obj = ref.toObject();
                HealthMarker h = HealthMarker::fromJson(obj);
                list << h;
            }

            f.close();
        }

    cont:
        days << list;
        prev = list;
    }

    return days;
}

bool HealthMarkerProgressManager::mkDate(int daysBack, QDir &dir) {
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
