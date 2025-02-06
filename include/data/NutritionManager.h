#ifndef NUTRITIONMANAGER_H
#define NUTRITIONMANAGER_H


#include <FoodItem.h>

#include <QDir>
#include <QObject>
#include <QQmlEngine>

class NutritionManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    QDate m_date;
    QDir m_dir;
public:
    NutritionManager(QObject *parent = nullptr);

    Q_INVOKABLE NutrientUnion load(int daysBack);

    QDate date() const;
    void setDate(const QDate &newDate);
    void resetDate();

signals:
    void dateChanged();

private:
    Q_PROPERTY(QDate date READ date WRITE setDate RESET resetDate NOTIFY dateChanged FINAL)
    bool mkDate(int daysBack, QDir &dir);
};

#endif // NUTRITIONMANAGER_H
