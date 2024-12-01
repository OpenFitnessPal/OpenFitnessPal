

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
    id: exercise

    color: Constants.sub1Color
    border.color: "#ffffff"
    border.width: 2

    signal deleteMe(int myId)
    signal exerciseChanged

    property alias remove: remove
    property alias add: add
    property alias listView: listView
    property alias exerciseName: exerciseName

    RemoveButton {
        id: remove

        anchors.left: parent.left
        anchors.leftMargin: 8

        anchors.top: parent.top
        anchors.topMargin: 8
    }

    TextField {
        id: exerciseName

        text: name

        height: 56
        color: "#ddf5f5f5"
        anchors.left: remove.right
        anchors.right: add.left
        anchors.top: parent.top
        anchors.leftMargin: 8
        anchors.rightMargin: 8
        anchors.topMargin: 8
        renderType: Text.NativeRendering

        font: Constants.subtitleFont

        placeholderText: qsTr("Exercise Name")
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
        anchors.top: exerciseName.bottom
        anchors.bottom: parent.bottom
        anchors.leftMargin: 20
        anchors.rightMargin: 0
        anchors.topMargin: 8
        anchors.bottomMargin: 0
        interactive: false

        model: esm
    }
}
