#ifndef CardioManager_H
#define CardioManager_H

#include <QObject>
#include <QDateTime>

#include <Cardio.h>
#include <QDir>

class CardioManager : public QObject
{
    Q_OBJECT

    QDateTime m_date;
    QDir m_dir;
public:
    CardioManager(QObject *parent);

    Q_INVOKABLE QList<Cardio> load();
    Q_INVOKABLE bool save(const QList<Cardio> &exercises);

    QDateTime date() const;
    void setDate(const QDateTime &newDate);
    void resetDate();
signals:
    void dateChanged();
private:
    Q_PROPERTY(QDateTime date READ date WRITE setDate RESET resetDate NOTIFY dateChanged FINAL)
    bool mkDate(QDir &dir);
};

#endif // CardioManager_H
