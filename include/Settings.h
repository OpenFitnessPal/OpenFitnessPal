#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QQmlEngine>

typedef struct Setting {
    const QString Name;
    const QVariant DefaultValue;

    QVariant value() const;
    void setValue(const QVariant &value) const;
} Setting;

class Settings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString meal1Name READ meal1Name WRITE setMeal1Name NOTIFY meal1NameChanged FINAL)
    Q_PROPERTY(QString meal2Name READ meal2Name WRITE setMeal2Name NOTIFY meal2NameChanged FINAL)
    Q_PROPERTY(QString meal3Name READ meal3Name WRITE setMeal3Name NOTIFY meal3NameChanged FINAL)
    Q_PROPERTY(QString meal4Name READ meal4Name WRITE setMeal4Name NOTIFY meal4NameChanged FINAL)
    Q_PROPERTY(QString meal5Name READ meal5Name WRITE setMeal5Name NOTIFY meal5NameChanged FINAL)
    QML_ELEMENT

public:
    Settings(QObject *parent = nullptr);

    static const Setting FirstRun;
    static const Setting Meal1Name;
    static const Setting Meal2Name;
    static const Setting Meal3Name;
    static const Setting Meal4Name;
    static const Setting Meal5Name;

    QString meal1Name() const;
    void setMeal1Name(const QString &newMeal1Name);

    QString meal2Name() const;
    void setMeal2Name(const QString &newMeal2Name);

    QString meal3Name() const;
    void setMeal3Name(const QString &newMeal3Name);

    QString meal4Name() const;
    void setMeal4Name(const QString &newMeal4Name);

    QString meal5Name() const;
    void setMeal5Name(const QString &newMeal5Name);

signals:
    void meal1NameChanged();

    void meal2NameChanged();

    void meal3NameChanged();

    void meal4NameChanged();

    void meal5NameChanged();

private:
    QString m_meal1Name;
    QString m_meal2Name;
    QString m_meal3Name;
    QString m_meal4Name;
    QString m_meal5Name;
};


#endif // SETTINGS_H
