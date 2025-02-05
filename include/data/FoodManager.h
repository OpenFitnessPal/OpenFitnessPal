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
    int m_meal;
public:
    FoodManager(QObject *parent = nullptr);

    Q_INVOKABLE bool save(const QList<FoodServing> &foods);
    Q_INVOKABLE QList<FoodServing> load();

    QDate date() const;
    void setDate(const QDate &newDate);
    void resetDate();

    int meal() const;
    void setMeal(int newMeal);

signals:
    void dateChanged();
    void mealChanged();

private:
    Q_PROPERTY(QDate date READ date WRITE setDate RESET resetDate NOTIFY dateChanged FINAL)
    bool mkDate(QDir &dir);
    Q_PROPERTY(int meal READ meal WRITE setMeal NOTIFY mealChanged FINAL REQUIRED)
};

#endif // FOODMANAGER_H
