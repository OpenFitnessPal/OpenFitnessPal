#ifndef GOALMANAGER_H
#define GOALMANAGER_H

#include "DataManager.h"

#include <QDir>
#include <QObject>
#include <QQmlEngine>

class GoalManager : public DataManager
{
    Q_OBJECT
    QML_ELEMENT

    // Helpers for frequently-used values
    Q_PROPERTY(int calories READ calories WRITE setCalories NOTIFY caloriesChanged FINAL)

    Q_PROPERTY(int carbs READ carbs WRITE setCarbs NOTIFY carbsChanged FINAL)
    Q_PROPERTY(int fat READ fat WRITE setFat NOTIFY fatChanged FINAL)
    Q_PROPERTY(int protein READ protein WRITE setProtein NOTIFY proteinChanged FINAL)

    Q_PROPERTY(int carbsGrams READ carbsGrams NOTIFY carbsGramsChanged FINAL)
    Q_PROPERTY(int fatGrams READ fatGrams  NOTIFY fatGramsChanged FINAL)
    Q_PROPERTY(int proteinGrams READ proteinGrams  NOTIFY proteinGramsChanged FINAL)

    int m_calories = -1;

    int m_carbs = -1;
    int m_fat = -1;
    int m_protein = -1;

    QMap<QString, int> m_fields;

public:
    GoalManager(QObject *parent = nullptr);

    Q_INVOKABLE bool set(const QString &field, const int data);
    Q_INVOKABLE int get(const QString &key, const int defaultValue);

    Q_INVOKABLE int getMacroGrams(const int value, const int caloriesPerGram = 4);

    int calories();
    void setCalories(int newCalories);

    int carbs();
    void setCarbs(int newCarbs);

    int fat();
    void setFat(int newFat);

    int protein();
    void setProtein(int newProtein);

    int carbsGrams();
    int fatGrams();
    int proteinGrams();

    void updateFields();
signals:
    void goalChanged(const QString &goal, const int newGoal);

    void caloriesChanged();

    void carbsChanged();
    void fatChanged();
    void proteinChanged();

    void carbsGramsChanged();
    void fatGramsChanged();
    void proteinGramsChanged();
};

#endif // GOALMANAGER_H
