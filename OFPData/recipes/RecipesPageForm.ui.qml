

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15

import OFPData


Rectangle {
    id: rectangle
    width: Constants.width
    height: Constants.pageHeight
    color: Constants.baseColor

    property alias add: add
    property alias listView: listView

    Text {
        id: text1
        color: "#ffffff"
        text: qsTr("Recipes")
        anchors.top: parent.top
        anchors.topMargin: 8
        font: Constants.titleFont

        anchors.horizontalCenter: parent.horizontalCenter
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
        anchors.bottomMargin: 40

        boundsMovement: Flickable.StopAtBounds
        boundsBehavior: Flickable.StopAtBounds
    }
}
