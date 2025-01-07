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

    Q_INVOKABLE bool set(const QString &field, const QVariant &data);
    Q_INVOKABLE QVariant get(const QString &key, const QVariant &defaultValue) const;

    QDate date() const;
    void setDate(const QDate &newDate);
    void resetDate();

signals:
    void dateChanged();

private:
    bool mkDate(QDir &dir) const;
    Q_PROPERTY(QDate date READ date WRITE setDate RESET resetDate NOTIFY dateChanged FINAL)
};

#endif // GOALMANAGER_H
