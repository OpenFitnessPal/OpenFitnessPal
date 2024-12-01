

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 6.2
import QtQuick.Controls 6.2

import OpenFitnessPalContent

import QtQuick.Layouts

Rectangle {
    id: exercisePageForm

    signal routinesRequested

    width: Constants.width
    height: Constants.pageHeight
    color: Constants.baseColor

    property date currentDate

    property alias add: add
    property alias listView: listView
    property alias routines: routines

    Text {
        id: title
        color: "#ffffff"
        text: "Exercises"

        anchors.top: parent.top
        anchors.topMargin: 10

        font: Constants.titleFont

        anchors.horizontalCenter: parent.horizontalCenter
    }

    AddButton {
        id: add
        anchors.right: parent.right
        anchors.rightMargin: 15
        anchors.top: parent.top
        anchors.topMargin: 7
    }

    ListView {
        id: listView
        clip: true

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: add.bottom
        anchors.bottom: parent.bottom

        anchors.leftMargin: 5
        anchors.rightMargin: 0
        anchors.topMargin: 15
        anchors.bottomMargin: 8
        boundsMovement: Flickable.StopAtBounds
        boundsBehavior: Flickable.StopAtBounds
    }

    Button {
        id: routines
        text: qsTr("Routines")
        anchors.verticalCenter: title.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 10

        font: Constants.subSubtitleFont
    }
}
