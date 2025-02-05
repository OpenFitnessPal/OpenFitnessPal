#ifndef GOALMANAGER_H
#define GOALMANAGER_H

#include <QDir>
#include <QObject>
#include <QQmlEngine>

class GoalManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    QDate m_date;
    QDir m_dir;
public:
    GoalManager(QObject *parent = nullptr);

    Q_INVOKABLE bool set(const QString &field, const int data);
    Q_INVOKABLE int get(const QString &key, const int defaultValue);

    Q_INVOKABLE int getMacroGrams(const QString &key, const int defaultValue, const int caloriesPerGram = 4);

    QDate date() const;
    void setDate(const QDate &newDate);
    void resetDate();

signals:
    void dateChanged();
    void goalChanged(const QString &goal, const int newGoal);

private:
    bool mkDate(QDir &dir) const;
    Q_PROPERTY(QDate date READ date WRITE setDate RESET resetDate NOTIFY dateChanged FINAL)
    void fixDateIfNotExists(QFile &f, QDir &dir, bool modify);
};

#endif // GOALMANAGER_H
