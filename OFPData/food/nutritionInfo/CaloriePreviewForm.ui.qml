

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
    // width: 480
    height: 100
    color: Constants.sub1Color

    signal clicked

    property alias goal: goal
    property alias food: food
    property alias remaining: remaining
    property alias mouse: mouse

    MouseArea {
        id: mouse
        anchors.fill: parent

        Text {
            id: title
            color: "#ffffff"

            anchors.left: parent.left
            anchors.leftMargin: 20
            font: Constants.mediumFont

            text: qsTr("Calories Remaining")
        }

        Text {
            id: goal
            color: "#ffffff"

            text: qsTr("10000")
            anchors.left: title.left
            anchors.top: title.bottom
            anchors.leftMargin: 5
            anchors.topMargin: 10
            font: Constants.mediumFont
        }

        Text {
            id: text1
            color: "#d4d4d4"
            text: qsTr("Goal")
            anchors.top: goal.bottom
            anchors.topMargin: 8
            font: Constants.smallFont
            anchors.horizontalCenter: goal.horizontalCenter
        }

        Text {
            id: food
            color: "#ffffff"

            text: qsTr("10000")

            anchors.top: title.bottom
            anchors.topMargin: 10

            font: Constants.mediumFont
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            id: text2
            color: "#d4d4d4"
            text: qsTr("Food")
            anchors.top: food.bottom
            anchors.topMargin: 8

            font: Constants.smallFont
            anchors.horizontalCenter: food.horizontalCenter
        }

        Text {
            id: text3

            text: qsTr("-")
            anchors.verticalCenter: food.verticalCenter
            font.pointSize: 30

            color: "#ffffff"

            x: ((goal.x + goal.width) + (food.x - food.width / 2.)) / 2.
        }

        Text {
            id: remaining
            color: "#ffffff"

            text: qsTr("10000")

            anchors.top: title.bottom
            anchors.topMargin: 10

            font: Constants.boldMediumFont
            anchors.right: parent.right

            anchors.rightMargin: 25
        }

        Text {
            id: text4
            color: "#d4d4d4"
            text: qsTr("Remaining")
            anchors.top: remaining.bottom
            anchors.topMargin: 8

            font: Constants.smallFont
            anchors.horizontalCenter: remaining.horizontalCenter
        }

        Text {
            id: text5

            text: qsTr("=")
            anchors.verticalCenter: food.verticalCenter
            font.pointSize: 30

            color: "#ffffff"

            x: ((food.x + food.width) + (remaining.x - remaining.width / 2.)) / 2.
        }
    }
}
