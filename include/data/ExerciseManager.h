#ifndef EXERCISEMANAGER_H
#define EXERCISEMANAGER_H

#include <QObject>
#include <QDate>

#include <Exercise.h>
#include <QDir>

class ExerciseManager : public QObject
{
    Q_OBJECT

    QDate m_date;
    QDir m_dir;
public:
    ExerciseManager(QObject *parent);

    Q_INVOKABLE QList<Exercise> load();
    Q_INVOKABLE bool save(const QList<Exercise> &exercises);

    QDate date() const;
    void setDate(const QDate &newDate);
    void resetDate();
signals:
    void dateChanged();
private:
    Q_PROPERTY(QDate date READ date WRITE setDate RESET resetDate NOTIFY dateChanged FINAL)
    bool mkDate(QDir &dir);
};

#endif // EXERCISEMANAGER_H
