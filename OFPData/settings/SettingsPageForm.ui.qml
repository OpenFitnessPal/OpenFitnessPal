

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 6.2
import QtQuick.Controls 6.2
import QtQuick.VirtualKeyboard 6.2
import OFPData
import QtQuick.Layouts

Rectangle {
    id: rectangle
    width: Constants.width
    height: Constants.pageHeight
    color: Constants.baseColor

    property alias title: title

    property alias meal1Name: meal1Name
    property alias meal2Name: meal2Name
    property alias meal3Name: meal3Name
    property alias meal4Name: meal4Name
    property alias meal5Name: meal5Name

    Text {
        id: title
        color: "#ffffff"
        text: "Settings"
        anchors.top: parent.top
        anchors.topMargin: 10
        font: Constants.titleFont

        anchors.horizontalCenter: parent.horizontalCenter
    }

    GridLayout {
        id: grid

        anchors.left: parent.left
        anchors.top: title.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        anchors.leftMargin: 15
        anchors.rightMargin: 15
        anchors.bottomMargin: 40
        anchors.topMargin: 8

        rows: 1
        flow: GridLayout.TopToBottom

        columns: 2

        Text {
            id: meal1
            color: "#ffffff"
            text: qsTr("Meal 1 Name:")

            anchors.leftMargin: 20
            anchors.topMargin: 10

            font: Constants.underlinedSubtitleFont


            Layout.row: 0
            Layout.column: 0
        }

        TextField {
            id: meal1Name
            height: 35
            color: "#ffffff"

            font: Constants.largeFont

            Layout.fillWidth: true
            Layout.row: 0
            Layout.column: 1
        }

        Text {
            id: meal2
            x: 22
            color: "#ffffff"
            text: qsTr("Meal 2 Name:")
            anchors.leftMargin: 20
            anchors.topMargin: 20
            font: Constants.underlinedSubtitleFont


            Layout.row: 1
            Layout.column: 0
        }

        TextField {
            id: meal2Name
            y: 60
            height: 35
            color: "#ffffff"
            font: Constants.largeFont

            Layout.row: 1
            Layout.fillWidth: true
            Layout.column: 1
        }

        Text {
            id: meal3
            x: 22
            color: "#ffffff"
            text: qsTr("Meal 3 Name:")
            anchors.leftMargin: 20
            anchors.topMargin: 20
            font: Constants.underlinedSubtitleFont


            Layout.row: 2
            Layout.column: 0
        }

        TextField {
            id: meal3Name
            y: 60
            height: 35
            color: "#ffffff"

            font: Constants.largeFont

            Layout.row: 2
            Layout.fillWidth: true
            Layout.column: 1
        }

        Text {
            id: meal4
            x: 22
            color: "#ffffff"
            text: qsTr("Meal 4 Name:")
            anchors.leftMargin: 20
            anchors.topMargin: 20
            font: Constants.underlinedSubtitleFont


            Layout.row: 3
            Layout.column: 0
        }

        TextField {
            id: meal4Name
            y: 60
            height: 35
            color: "#ffffff"

            font: Constants.largeFont

            Layout.row: 3
            Layout.fillWidth: true
            Layout.column: 1
        }

        Text {
            id: meal5
            x: 22
            color: "#ffffff"
            text: qsTr("Meal 5 Name:")
            anchors.leftMargin: 20
            anchors.topMargin: 20
            font: Constants.underlinedSubtitleFont


            Layout.row: 4
            Layout.column: 0
        }

        TextField {
            id: meal5Name
            y: 60
            height: 35
            color: "#ffffff"

            font: Constants.largeFont

            Layout.row: 4
            Layout.fillWidth: true
            Layout.column: 1
        }
    }
    // }
}
