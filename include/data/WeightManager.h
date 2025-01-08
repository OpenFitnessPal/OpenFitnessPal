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

    Q_PROPERTY(QDate date READ date WRITE setDate RESET resetDate NOTIFY dateChanged FINAL)
    Q_PROPERTY(int weight READ get WRITE set NOTIFY weightChanged FINAL)
public:
    WeightManager(QObject *parent = nullptr);

    Q_INVOKABLE bool set(const int weight);
    Q_INVOKABLE int get();

    QDate date() const;
    void setDate(const QDate &newDate);
    void resetDate();

signals:
    void dateChanged();
    void weightChanged();

private:
    bool mkDate(QDir &dir) const;
    void fixDateIfNotExists(QFile &f, QDir &dir, bool modify);
};

#endif // WEIGHTMANAGER_H
