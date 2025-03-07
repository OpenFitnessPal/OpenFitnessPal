#ifndef MEALNAMESMANAGER_H
#define MEALNAMESMANAGER_H

#include <QDir>
#include <QObject>
#include <QQmlEngine>

class MealNamesManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    QDateTime m_date;
    QDir m_dir;

    QStringList m_mealNames;
public:
    MealNamesManager(QObject *parent = nullptr);

    Q_INVOKABLE bool save();
    Q_INVOKABLE QStringList load();

    QStringList mealNames() const;
    void setMealNames(const QStringList &newMealNames);


signals:
    void mealNamesChanged();

private:
    Q_PROPERTY(QStringList mealNames READ mealNames WRITE setMealNames NOTIFY mealNamesChanged FINAL)
};

#endif // MEALNAMESMANAGER_H
