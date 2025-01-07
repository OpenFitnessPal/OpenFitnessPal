#ifndef FOODMANAGER_H
#define FOODMANAGER_H

#include <FoodItem.h>

#include <QDir>
#include <QObject>
#include <QQmlEngine>

class FoodManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    QDate m_date;
    QDir m_dir;
public:
    FoodManager(QObject *parent = nullptr);

    Q_INVOKABLE bool save(int meal, const QList<FoodServing> &foods);
    Q_INVOKABLE QList<FoodServing> load(int meal);

    QDate date() const;
    void setDate(const QDate &newDate);
    void resetDate();

signals:
    void dateChanged();
private:
    Q_PROPERTY(QDate date READ date WRITE setDate RESET resetDate NOTIFY dateChanged FINAL)
    bool mkDate(QDir &dir);
};

#endif // FOODMANAGER_H
