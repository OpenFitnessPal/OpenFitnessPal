import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

import OFPData

Rectangle {
    id: root
    height: 40
    width: 450

    signal goalChanged(var newGoal)

    property int index

    color: Constants.baseColor

    Text {
        id: text1
        color: "#ffffff"

        text: qsTr("Goal:")
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 0
        font: Constants.mediumFont
    }

    GoalSpinBox {
        anchors.left: parent.horizontalCenter
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.leftMargin: 0
        anchors.rightMargin: 0
        anchors.topMargin: 0
        anchors.bottomMargin: 0

        Layout.fillWidth: true

        function sendIndex() {
            index = value
            goalChanged(value)
        }

        Component.onCompleted: {
            value = goalManager.get("goal")
            index = value

            valueChanged.connect(sendIndex)
        }
    }
}
