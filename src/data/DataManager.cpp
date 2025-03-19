#include "data/DataManager.h"

#include <QDirIterator>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

DataManager::DataManager(QObject *parent)
    : QObject(parent)
{
    resetDate();
    m_dir = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    m_dir.mkpath(".");
}

QDateTime DataManager::date() const
{
    return m_date;
}

void DataManager::setDate(const QDateTime &newDate)
{
    if (m_date == newDate)
        return;
    m_date = newDate;
    emit dateChanged();
}

void DataManager::resetDate()
{
    setDate(QDateTime::currentDateTime());
}

QByteArray DataManager::read()
{
    QDir dir(m_dir);

    if (m_useDate) mkDate(dir);
    if (!m_subdir.isEmpty()) {
        dir.mkpath(m_subdir);
        dir.cd(m_subdir);
    }

    QFile file(dir.absoluteFilePath(m_filename));

    if (m_nearest) findNearest(file, dir, false);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return "";
    }

    QByteArray data = file.readAll();

    file.close();

    return data;
}

QJsonDocument DataManager::readDoc()
{
    return QJsonDocument::fromJson(read());
}

QJsonObject DataManager::readObject()
{
    return readDoc().object();
}

QJsonArray DataManager::readArray()
{
    return readDoc().array();
}

bool DataManager::write(const QByteArray &data)
{
    QDir dir(m_dir);

    if (m_useDate) mkDate(dir);

    if (!m_subdir.isEmpty()) {
        dir.mkpath(m_subdir);
        dir.cd(m_subdir);
    }

    QFile file(dir.absoluteFilePath(m_filename));

    if (m_nearest) findNearest(file, dir, true);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        return false;
    }

    int bytes = file.write(data);

    file.close();

    return bytes != -1;
}

bool DataManager::write(const QJsonDocument &doc)
{
    return write(doc.toJson());
}

bool DataManager::write(const QJsonArray &arr)
{
    return write(QJsonDocument(arr));
}

bool DataManager::write(const QJsonObject &obj)
{
    return write(QJsonDocument(obj));
}

bool DataManager::mkDate(QDir &dir)
{
    QString dateString = m_date.toString("MM-dd-yyyy");

    if (!dir.mkpath(dateString)) {
        return false;
    }

    dir.cd(dateString);
    return true;
}

void DataManager::findNearest(QFile &f, QDir &dir, bool modify)
{
    if (!f.exists() || !(modify || dir.exists(m_modifiedFileName))) {
        QDir rootDir(m_dir);

        QDateTime closestDate = QDateTime(QDate(1, 1, 1), QTime(0, 0, 0, 0));

        QDirIterator iter(rootDir);
        while (iter.hasNext()) {
            iter.next();
            QString dirName = iter.fileName();
            QDir dir = rootDir.absoluteFilePath(dirName);

            if (!dir.exists(m_filename) || !dir.exists(m_modifiedFileName)) continue;

            QDateTime date = QDateTime::fromString(dirName, "MM-dd-yyyy");

            if (date.isNull() || date == m_date) continue;

            int distance = std::abs(date.daysTo(m_date));

            if (distance < closestDate.daysTo(m_date) && distance != 0) {
                closestDate = date;
            }
        }

        if (closestDate != QDateTime(QDate(1, 1, 1), QTime(0, 0, 0, 0))) {
            QString original = m_dir.absoluteFilePath(closestDate.toString("MM-dd-yyyy") + "/" + m_filename);

            // Remove the original in case it exists and is unmodified
            QFile::remove(dir.absoluteFilePath(m_filename));
            QFile::copy(original, dir.absoluteFilePath(m_filename));
        } else {
            if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
                return;
            }

            f.close();
        }
    } else if (modify) {
        QFile modified(dir.absoluteFilePath(m_modifiedFileName));
        if (!modified.exists()) {
            modified.open(QIODevice::WriteOnly);
            modified.close();
        }
    }
}
