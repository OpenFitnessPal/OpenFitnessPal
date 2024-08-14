

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
    id: routineEdit

    signal addRoutine(var routine)
    signal closeOut

    width: Constants.width
    height: Constants.pageHeight
    color: Constants.baseColor

    property var routine

    property alias back: back
    property alias add: add

    property alias routineName: routineName
    property alias routineNotes: routineNotes

    property alias addExercise: addExercise
    property alias exercises: exercises

    TextField {
        id: routineName
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: back.bottom
        anchors.leftMargin: 15
        anchors.rightMargin: 15
        anchors.topMargin: 4

        font: Constants.subtitleFont

        text: routine.name
        placeholderText: qsTr("Routine Name")
    }

    TextArea {
        id: routineNotes

        color: "#888888"
        font: Constants.subSubtitleFont

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: routineName.bottom
        anchors.leftMargin: 8
        anchors.rightMargin: 8
        anchors.topMargin: 8

        placeholderText: qsTr("Notes")
    }

    RemoveButton {
        id: back

        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 8
        anchors.topMargin: 4
    }

    ListView {
        id: exercises

        clip: true

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: routineNotes.bottom
        anchors.bottom: addExercise.top
        anchors.leftMargin: 8
        anchors.rightMargin: 8
        anchors.topMargin: 8
        anchors.bottomMargin: 8

        boundsMovement: Flickable.StopAtBounds
        boundsBehavior: Flickable.StopAtBounds
    }

    AddButton {
        id: add

        anchors.right: parent.right
        anchors.top: parent.top

        anchors.rightMargin: 8
        anchors.topMargin: 4
    }

    Button {
        id: addExercise

        font: Constants.subtitleFont

        text: qsTr("Add Exercise")
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.leftMargin: 15
        anchors.rightMargin: 15
        anchors.bottomMargin: 4
    }
}
