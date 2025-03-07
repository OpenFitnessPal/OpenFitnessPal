#include "data/WeightManager.h"

#include <QDirIterator>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

WeightManager::WeightManager(QObject *parent)
    : QObject{parent}
{
    m_dir = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);

    resetDate();
}

QDateTime WeightManager::date() const
{
    return m_date;
}

void WeightManager::setDate(const QDateTime &newDate)
{
    if (m_date == newDate)
        return;
    m_date = newDate;
    emit dateChanged();
    emit weightChanged();

}

void WeightManager::resetDate()
{
    setDate(QDateTime::currentDateTime());
}

bool WeightManager::set(const int weight)
{
    QDir dir(m_dir);
    mkDate(dir);

    QFile f(dir.absoluteFilePath("weight"));

    fixDateIfNotExists(f, dir, true);

    if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        return false;
    }

    f.write(QByteArray::number(weight));
    f.close();

    emit weightChanged();

    return true;
}


int WeightManager::get()
{
    QDir dir(m_dir);

    mkDate(dir);

    QFile f(dir.absoluteFilePath("weight"));
    fixDateIfNotExists(f, dir, false);

    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return 135;
    }

    int weight = f.readAll().toInt();

    f.close();

    return weight;
}

bool WeightManager::mkDate(QDir &dir) const {
    QString dateString = m_date.toString("MM-dd-yyyy");

    if (!dir.mkpath(dateString)) {
        return false;
    }

    dir.cd(dateString);
    return true;
}

void WeightManager::fixDateIfNotExists(QFile &f, QDir &dir, bool modify)
{
    if (!f.exists() || (!modify && !dir.exists("weightModified"))) {
        QDir rootDir(m_dir);

        QDateTime closestDate = QDateTime(QDate(1, 1, 1), QTime(0, 0, 0, 0));

        QDirIterator iter(rootDir);
        while (iter.hasNext()) {
            iter.next();
            QString dirName = iter.fileName();
            QDateTime date = QDateTime::fromString(dirName, "MM-dd-yyyy");

            if (date.isNull() || date == m_date) continue;

            int distance = date.daysTo(m_date);

            if (distance < closestDate.daysTo(m_date)) {
                closestDate = date;
            }
        }

        if (closestDate != QDateTime(QDate(1, 1, 1), QTime(0, 0, 0, 0))) {
            QString original = m_dir.absoluteFilePath(closestDate.toString("MM-dd-yyyy") + "/weight");

            // Remove the original in case it exists and is unmodified
            QFile::remove(dir.absoluteFilePath("weight"));
            QFile::copy(original, dir.absoluteFilePath("weight"));
        } else {
            if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
                return;
            }

            f.write("135");
            f.close();
        }
    } else if (modify) {
        QFile modified(dir.absoluteFilePath("weightModified"));
        if (!modified.exists()) {
            modified.open(QIODevice::WriteOnly);
            modified.close();
        }
    }
}
