#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QVariant>

typedef struct Setting {
    const QString Name;
    const QVariant DefaultValue;

    QVariant value() const;
    void setValue(const QVariant &value) const;
} Setting;

namespace Settings {
extern const Setting FirstRun;
extern const Setting Meal1Name;
extern const Setting Meal2Name;
extern const Setting Meal3Name;
extern const Setting Meal4Name;
extern const Setting Meal5Name;
}

#endif // SETTINGS_H
