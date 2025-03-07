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

    QDateTime m_date;
    QDir m_dir;

    NutrientUnion m_today;
    NutrientUnion m_week;
    QList<NutrientUnion> m_weekList;

public:
    NutritionManager(QObject *parent = nullptr);

    Q_INVOKABLE NutrientUnion load(int daysBack);
    Q_INVOKABLE QList<NutrientUnion> list(int daysBack);

    QDateTime date() const;
    void setDate(const QDateTime &newDate);
    void resetDate();

    NutrientUnion today() const;
    NutrientUnion week() const;
    QList<NutrientUnion> weekList() const;

    Q_INVOKABLE void updateNutrients();

signals:
    void dateChanged();

    void todayChanged();

    void weekChanged();

    void weekListChanged();

private:
    Q_PROPERTY(QDateTime date READ date WRITE setDate RESET resetDate NOTIFY dateChanged FINAL)
    bool mkDate(int daysBack, QDir &dir);

    Q_PROPERTY(NutrientUnion today READ today NOTIFY todayChanged FINAL)
    Q_PROPERTY(NutrientUnion week READ week NOTIFY weekChanged FINAL)
    Q_PROPERTY(QList<NutrientUnion> weekList READ weekList NOTIFY weekListChanged FINAL)
};

#endif // NUTRITIONMANAGER_H
