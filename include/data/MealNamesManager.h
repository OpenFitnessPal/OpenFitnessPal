#ifndef MEALNAMESMANAGER_H
#define MEALNAMESMANAGER_H

#include <QDir>
#include <QObject>
#include <QQmlEngine>

class MealNamesManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    QDate m_date;
    QDir m_dir;

    QStringList m_mealNames;
public:
    MealNamesManager(QObject *parent = nullptr);

    Q_INVOKABLE bool save();
    Q_INVOKABLE QStringList load();

    QDate date() const;
    void setDate(const QDate &newDate);
    void resetDate();

    QStringList mealNames() const;
    void setMealNames(const QStringList &newMealNames);


signals:
    void dateChanged();

    void mealNamesChanged();

private:
    Q_PROPERTY(QDate date READ date WRITE setDate RESET resetDate NOTIFY dateChanged FINAL)
    Q_PROPERTY(QStringList mealNames READ mealNames WRITE setMealNames NOTIFY mealNamesChanged FINAL)
    bool mkDate(QDir &dir) const;
    void fixDateIfNotExists(QFile &f, QDir &dir, bool modify);
};

#endif // MEALNAMESMANAGER_H
