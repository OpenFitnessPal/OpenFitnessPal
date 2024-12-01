

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15

import OpenFitnessPal

Rectangle {
    id: exercisePageForm

    signal closeOut
    signal editRoutine(int id, var routine)

    width: Constants.width
    height: Constants.pageHeight
    color: Constants.baseColor

    property alias back: back
    property alias add: add
    property alias routines: routines

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

    ListView {
        id: routines

        clip: true

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: text1.bottom
        anchors.bottom: parent.bottom
        anchors.leftMargin: 8
        anchors.rightMargin: 8
        anchors.topMargin: 20
        anchors.bottomMargin: 8
    }

    AddButton {
        id: add

        anchors.right: parent.right
        anchors.top: parent.top

        anchors.rightMargin: 8
        anchors.topMargin: 4
    }
}
