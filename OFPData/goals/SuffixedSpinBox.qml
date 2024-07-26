/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/

import QtQuick 2.15
import QtQuick.Controls 2.15

SpinBox {
    property string suffix: "%"

    textFromValue: function(value, locale) {
        return value + suffix
    }

    valueFromText: function(text, locale) {
        console.log(text)
        console.log(text.replace(suffix, ""))
        console.log(Number.fromLocaleString(locale, text.replace(suffix, "")))
        return Number.fromLocaleString(locale, text.replace(suffix, ""))
        // return 30
    }
}
