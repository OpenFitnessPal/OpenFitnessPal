

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 6.2
import QtQuick.Controls 6.2
import QtQuick.VirtualKeyboard 6.2
import OpenFitnessPalContent
import QtQuick.Layouts

Rectangle {
    id: rectangle
    width: Constants.width
    height: Constants.pageHeight
    color: Constants.baseColor

    signal mealNamesChanged

    property alias title: title

    property alias cacheDir: cacheDir
    property alias dataDir: dataDir
    property alias repeater: repeater
    property alias searchSettings: searchSettings

    Text {
        id: title
        color: "#ffffff"
        text: "Settings"
        anchors.top: parent.top
        anchors.topMargin: 10
        font: Constants.titleFont

        anchors.horizontalCenter: parent.horizontalCenter
    }

    ColumnLayout {
        id: grid

        anchors.left: parent.left
        anchors.top: title.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        anchors.leftMargin: 15
        anchors.rightMargin: 15
        anchors.bottomMargin: 40
        anchors.topMargin: 8

        Repeater {
            id: repeater
            model: ["Breakfast", "Lunch", "Dinner", "Preworkout", "Postworkout"]
        }

        DirSetting {
            id: cacheDir
            isCache: true

            Layout.fillWidth: true
        }

        DirSetting {
            id: dataDir
            isCache: false

            Layout.fillWidth: true
        }

        Button {
            id: searchSettings

            text: "Search Settings..."
            Layout.fillWidth: true
        }
    }
}
