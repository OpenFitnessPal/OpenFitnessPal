import QtQuick

import OFPItems
import Util

Rectangle {
    required property string title

    color: Constants.bg

    Shortcut {
        sequence: Qt.Key_Back
        onActivated: {
            console.log("Back")
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
            leftMargin: 30
        }
    }

    Text {
        font.pixelSize: 25 * Constants.scalar
        color: Constants.text

        text: title

        anchors {
            verticalCenter: nav.verticalCenter

            horizontalCenter: parent.horizontalCenter
        }
    }
}
