

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 6.2
import QtQuick.Controls 6.2
import QtQuick.VirtualKeyboard 6.2
import OFPData
import QtQuick.Layouts

Rectangle {
    id: rectangle
    width: Constants.width
    height: Constants.pageHeight
    color: Constants.baseColor

    property alias title: title

    property alias meal1: meal1
    property alias meal2: meal2
    property alias meal3: meal3
    property alias meal4: meal4
    property alias meal5: meal5

    Text {
        id: title
        color: "#ffffff"
        text: "Settings"
        anchors.top: parent.top
        anchors.topMargin: 10
        font: Constants.titleFont

        anchors.horizontalCenter: parent.horizontalCenter
    }

    GridLayout {
        id: grid

        anchors.left: parent.left
        anchors.top: title.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        anchors.leftMargin: 15
        anchors.rightMargin: 15
        anchors.bottomMargin: 40
        anchors.topMargin: 8

        flow: GridLayout.TopToBottom

        MealNameSetting {
            id: meal1
            mealNumber: 1
            defaultName: "Breakfast"

            Layout.column: 0
            Layout.fillWidth: true
            Layout.row: 0
        }

        MealNameSetting {
            id: meal2
            mealNumber: 2
            defaultName: "Lunch"

            Layout.column: 0
            Layout.fillWidth: true
            Layout.row: 1
        }

        MealNameSetting {
            id: meal3
            mealNumber: 3
            defaultName: "Dinner"

            Layout.column: 0
            Layout.fillWidth: true
            Layout.row: 2
        }

        MealNameSetting {
            id: meal4
            mealNumber: 4
            defaultName: "Preworkout"

            Layout.column: 0
            Layout.fillWidth: true
            Layout.row: 3
        }

        MealNameSetting {
            id: meal5
            mealNumber: 5
            defaultName: "Postworkout"

            Layout.column: 0
            Layout.fillWidth: true
            Layout.row: 4
        }

        DirSetting {
            id: cacheDir
            isCache: true

            Layout.column: 0
            Layout.fillWidth: true
            Layout.row: 5
        }

        DirSetting {
            id: dataDir
            isCache: false

            Layout.column: 0
            Layout.fillWidth: true
            Layout.row: 6
        }
    }
}
