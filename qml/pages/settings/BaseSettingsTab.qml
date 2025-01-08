import QtQuick

import OpenFitnessPal

Rectangle {
    required property string title

    property alias nav: nav

    color: Constants.bg

    Shortcut {
        sequence: Qt.Key_Back
        onActivated: {
            stack.pop()
        }
    }

    NavButton {
        id: nav
        width: 40 * Constants.scalar
        height: 40 * Constants.scalar

        label: "Back"
        onClicked: stack.pop()

        background: Item {}

        anchors {
            top: parent.top
            left: parent.left

            topMargin: 10
            leftMargin: 30 * Constants.scalar
        }
    }

    Text {
        font.pixelSize: Math.round(25 * Constants.scalar)
        color: Constants.text

        text: title

        anchors {
            verticalCenter: nav.verticalCenter

            horizontalCenter: parent.horizontalCenter
        }
    }
}
