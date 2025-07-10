#ifndef DATEMANAGER_H
#define DATEMANAGER_H

#include <QObject>
#include <QDateTime>

class DateManager : public QObject
{
    Q_OBJECT
    QDateTime m_date;
public:
    explicit DateManager(QObject *parent = nullptr);

    QDateTime date() const;
    void setDate(const QDateTime &newDate);

signals:
    void dateChanged();
private:
    Q_PROPERTY(QDateTime date READ date WRITE setDate NOTIFY dateChanged FINAL)
};

#endif // DATEMANAGER_H
