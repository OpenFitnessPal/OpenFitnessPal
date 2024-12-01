

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

import OpenFitnessPalContent

Rectangle {
    id: rectangle
    y: 0
    width: Constants.width
    height: Constants.pageHeight
    color: Constants.baseColor

    property date currentDate

    property alias swipe: swipe
    property alias journal: journal
    property alias nutrition: nutrition

    SwipeView {
        id: swipe
        clip: true
        anchors.fill: parent
        anchors.bottomMargin: 50
        interactive: false
        currentIndex: 0

        JournalPage {
            id: journal
            visible: true
        }

        NutritionInfo {
            id: nutrition
        }
    }
}
