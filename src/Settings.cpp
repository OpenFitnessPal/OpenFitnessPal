#include "Settings.h"

#include <QSettings>
#include <QApplication>

QVariant Setting::value() const {
    QSettings settings(qApp);
    return settings.value(Name, DefaultValue);
}

void Setting::setValue(const QVariant &value) const {
    QSettings settings(qApp);
    settings.setValue(Name, value);
}

const Setting Settings::FirstRun{"firstRun", true};

const Setting Settings::Meal1Name{"meal1Name", "Meal 1"};
const Setting Settings::Meal2Name{"meal2Name", "Meal 2"};
const Setting Settings::Meal3Name{"meal3Name", "Meal 3"};
const Setting Settings::Meal4Name{"meal4Name", "Meal 4"};
const Setting Settings::Meal5Name{"meal5Name", "Meal 5"};
