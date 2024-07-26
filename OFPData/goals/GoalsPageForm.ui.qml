

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15

import OFPData
import QtQuick.Layouts

Rectangle {
    id: rectangle
    width: Constants.width
    height: Constants.pageHeight
    color: Constants.baseColor

    Text {
        id: text1
        color: "#ffffff"
        text: qsTr("Goals")
        anchors.top: parent.top
        anchors.topMargin: 8
        font.pixelSize: 24
        font.bold: true
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Flickable {
        id: flickable

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: text1.bottom
        anchors.bottom: parent.bottom

        anchors.leftMargin: 8
        anchors.rightMargin: 8
        anchors.topMargin: 8
        anchors.bottomMargin: 8

        boundsMovement: Flickable.StopAtBounds
        boundsBehavior: Flickable.StopAtBounds
    }
}
