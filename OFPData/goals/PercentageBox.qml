/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/

import QtQuick 2.15
import QtQuick.Controls 2.15

SpinBox {
    from: 0
    to: 100
    value: 0

    textFromValue: function(value) {
        return value + "%"
    }

    valueFromText: function(text) {
        return text.substring(0, text.length - 1)
    }
}
