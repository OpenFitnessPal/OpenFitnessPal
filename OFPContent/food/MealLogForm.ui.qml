

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15

import OFPContent
import OFPData

Rectangle {
    id: rectangle

    color: Constants.sub1Color

    border.color: "#ffffff"

    border.width: 2

    property date currentDate

    property int mealNumber: 1
    property alias listView: listView
    property alias mealName: mealName
    property alias add: add

    Text {
        id: mealName

        color: "#ffffff"
        text: qsTr("Meal")

        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 50
        anchors.topMargin: 20

        font.pixelSize: 21
        font.bold: true
        font.weight: Font.Medium
    }

    AddButton {
        id: add

        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: 8
        anchors.topMargin: 8
    }

    ListView {
        id: listView
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: add.bottom
        anchors.bottom: parent.bottom
        anchors.leftMargin: 15
        anchors.rightMargin: 15
        anchors.topMargin: 15
        anchors.bottomMargin: 15
        boundsMovement: Flickable.StopAtBounds
        boundsBehavior: Flickable.StopAtBounds
        interactive: false
    }
}
