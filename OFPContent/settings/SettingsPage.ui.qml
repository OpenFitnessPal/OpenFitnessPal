

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

    Text {
        id: title
        color: "#ffffff"
        text: "Settings"
        anchors.top: parent.top
        anchors.topMargin: 10
        font.pixelSize: 24
        font.bold: true
        anchors.horizontalCenter: parent.horizontalCenter
        font.family: Constants.largeFont.family
    }

    // ScrollView {
    //     id: scrollView
    //     anchors.left: parent.left
    //     anchors.right: parent.right
    //     anchors.top: title.bottom
    //     anchors.bottom: parent.bottom

    //     anchors.leftMargin: 0
    //     anchors.rightMargin: 10
    //     anchors.topMargin: 0
    //     anchors.bottomMargin: 55

    // contentHeight: meal5.y

    // ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
    // ScrollBar.vertical.policy: ScrollBar.AlwaysOn
    GridLayout {
        id: grid
        anchors.left: parent.left
        anchors.top: title.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        anchors.leftMargin: 15
        anchors.rightMargin: 15
        anchors.bottomMargin: 10
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

            font.pixelSize: 20
            font.underline: true
            font.bold: false

            Layout.row: 0
            Layout.column: 0
        }

        TextField {
            id: meal1Name
            height: 35
            color: "#ffffff"
            text: qsTr(settings.meal1Name)

            font.pixelSize: 18

            Layout.fillWidth: true
            Layout.row: 0
            Layout.column: 1

            onEditingFinished: settings.meal1Name = text
        }

        Text {
            id: meal2
            x: 22
            color: "#ffffff"
            text: qsTr("Meal 2 Name:")
            anchors.leftMargin: 20
            anchors.topMargin: 20
            font.pixelSize: 20
            font.underline: true
            font.bold: false
            Layout.row: 1
            Layout.column: 0
        }

        TextField {
            id: meal2Name
            y: 60
            height: 35
            color: "#ffffff"
            text: qsTr(settings.meal2Name)
            font.pixelSize: 18
            onEditingFinished: settings.meal2Name = text
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
            font.pixelSize: 20
            font.underline: true
            font.bold: false
            Layout.row: 2
            Layout.column: 0
        }

        TextField {
            id: meal3Name
            y: 60
            height: 35
            color: "#ffffff"
            text: qsTr(settings.meal3Name)
            font.pixelSize: 18
            onEditingFinished: settings.meal3Name = text
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
            font.pixelSize: 20
            font.underline: true
            font.bold: false
            Layout.row: 3
            Layout.column: 0
        }

        TextField {
            id: meal4Name
            y: 60
            height: 35
            color: "#ffffff"
            text: qsTr(settings.meal4Name)
            font.pixelSize: 18
            onEditingFinished: settings.meal4Name = text
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
            font.pixelSize: 20
            font.underline: true
            font.bold: false
            Layout.row: 4
            Layout.column: 0
        }

        TextField {
            id: meal5Name
            y: 60
            height: 35
            color: "#ffffff"
            text: qsTr(settings.meal5Name)
            font.pixelSize: 18
            onEditingFinished: settings.meal5Name = text
            Layout.row: 4
            Layout.fillWidth: true
            Layout.column: 1
        }
    }
    // }
}
