

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15

import OpenFitnessPalContent

Rectangle {
    id: rectangle
    width: Constants.width
    height: Constants.pageHeight
    color: Constants.baseColor

    property alias swipe: swipe
    property alias main: main
    property alias search: search

    SwipeView {
        id: swipe
        interactive: false
        clip: true

        anchors.fill: parent
        anchors.bottomMargin: 40
        currentIndex: 0

        SettingsPage {
            id: main
        }

        SearchSettingsPage {
            id: search
        }
    }
}
