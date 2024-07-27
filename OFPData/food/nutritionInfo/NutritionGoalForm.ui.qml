

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
    width: 600
    height: 60
    color: Constants.sub1Color

    property string name: "Goal Name"
    property string internalName: "goal"
    property string suffix: "g"

    property alias goalName: goalName
    property alias amountLeft: amountLeft
    property alias total: total
    property alias progressBar: progressBar

    Text {
        id: goalName
        color: "#ffffff"

        text: qsTr(name)
        anchors.left: parent.left
        anchors.right: parent.horizontalCenter
        anchors.top: parent.top
        anchors.leftMargin: 15
        anchors.rightMargin: 0
        anchors.topMargin: 10
        font.pixelSize: 16
        verticalAlignment: Text.AlignVCenter
    }

    ProgressBar {
        id: progressBar
        y: 38
        value: 0.5
        anchors.left: goalName.left
        anchors.right: parent.right
        anchors.leftMargin: 0
        anchors.rightMargin: 15
    }

    Text {
        id: total
        color: "#ffffff"
        width: 50
        text: qsTr("10000.0")

        anchors.verticalCenter: goalName.verticalCenter
        anchors.left: goalName.right
        anchors.leftMargin: 8
        font.pixelSize: 14
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
    }

    Text {
        id: amountLeft
        width: 50

        x: ((total.x + total.width) + (goal.x - goal.width / 2.)) / 2.
        color: "#ffffff"
        text: qsTr("10000.0")
        anchors.verticalCenter: total.verticalCenter
        // anchors.left: total.right
        // anchors.leftMargin: 60
        font.pixelSize: 14
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
    }

    Text {
        id: goal
        width: 76
        color: "#ffffff"
        text: qsTr("10000.0kcal")

        anchors.verticalCenter: total.verticalCenter
        anchors.right: progressBar.right
        anchors.rightMargin: 0
        font.pixelSize: 14
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
    }
}
