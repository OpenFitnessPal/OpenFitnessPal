

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
    id: exercisePageForm

    signal closeOut

    width: Constants.width
    height: Constants.pageHeight
    color: Constants.baseColor

    property alias back: back

    Text {
        id: text1
        y: 17
        color: "#ffffff"
        text: qsTr("Routines")
        anchors.top: parent.top
        anchors.topMargin: 8
        anchors.horizontalCenter: parent.horizontalCenter
        font: Constants.titleFont
    }

    RemoveButton {
        id: back

        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 8
        anchors.topMargin: 4
    }
}
