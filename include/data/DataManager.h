#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QDateTime>
#include <QDir>


/* Base class for all OpenFitnessPal data management. */
class DataManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QDateTime date READ date WRITE setDate RESET resetDate NOTIFY dateChanged FINAL)
public:
    DataManager(QObject *parent);

    QDateTime date() const;
    void setDate(const QDateTime &newDate);
    void resetDate();

protected:
    bool m_useDate = false;
    bool m_nearest = false;
    QString m_filename = "";
    QString m_modifiedFileName = "";
    QString m_subdir = "";

    QDateTime m_date;
    QDir m_dir;

    QByteArray read();
    QJsonDocument readDoc();
    QJsonObject readObject();
    QJsonArray readArray();

    bool write(const QByteArray &data);
    bool write(const QJsonDocument &doc);
    bool write(const QJsonArray &arr);
    bool write(const QJsonObject &obj);

    bool mkDate(QDir &dir);

    void findNearest(QFile &f, QDir &dir, bool modify);

signals:
    void dateChanged();
};

#endif // DATAMANAGER_H
