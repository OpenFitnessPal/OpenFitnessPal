#ifndef CardioManager_H
#define CardioManager_H

#include <QObject>
#include <QDate>

#include <Cardio.h>
#include <QDir>

class CardioManager : public QObject
{
    Q_OBJECT

    QDate m_date;
    QDir m_dir;
public:
    CardioManager(QObject *parent);

    Q_INVOKABLE QList<Cardio> load();
    Q_INVOKABLE bool save(const QList<Cardio> &exercises);

    QDate date() const;
    void setDate(const QDate &newDate);
    void resetDate();
signals:
    void dateChanged();
private:
    Q_PROPERTY(QDate date READ date WRITE setDate RESET resetDate NOTIFY dateChanged FINAL)
    bool mkDate(QDir &dir);
};

#endif // CardioManager_H
