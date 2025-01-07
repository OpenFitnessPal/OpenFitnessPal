#ifndef WEIGHTMANAGER_H
#define WEIGHTMANAGER_H

#include <QDir>
#include <QObject>
#include <QQmlEngine>

class WeightManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    QDate m_date;
    QDir m_dir;

public:
    WeightManager(QObject *parent = nullptr);

    Q_INVOKABLE bool set(const QVariant &weight);
    Q_INVOKABLE QVariant get() const;

    QDate date() const;
    void setDate(const QDate &newDate);
    void resetDate();

signals:
    void dateChanged();

private:
    bool mkDate(QDir &dir) const;
    Q_PROPERTY(QDate date READ date WRITE setDate RESET resetDate NOTIFY dateChanged FINAL)
};

#endif // WEIGHTMANAGER_H
