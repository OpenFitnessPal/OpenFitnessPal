

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
    id: routine
    height: 80

    signal clicked

    color: Constants.sub1Color
    border.color: "#ffffff"
    border.width: 1

    property var routine

    property alias routineNotes: routineNotes
    property alias routineName: routineName

    property alias mouse: mouse

    MouseArea {
        id: mouse
        anchors.fill: parent

        Text {
            id: routineName
            text: qsTr("Routine Name")
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.leftMargin: 15
            anchors.topMargin: 8
            wrapMode: Text.WrapAnywhere
            color: "#ffffff"
            font: Constants.mediumSubtitleFont
        }

        Text {
            id: routineNotes
            y: 69
            color: "#888888"
            text: qsTr("Notes")
            elide: Text.ElideRight
            anchors.left: routineName.left
            anchors.bottom: parent.bottom
            anchors.leftMargin: 15
            anchors.bottomMargin: 6
            font: Constants.subSubtitleFont
        }
    }
}
