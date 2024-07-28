import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

import OFPData

Rectangle {
    id: rectangle
    color: "#000000"

    width: 480
    height: 60

    Text {
        id: total
        color: "#ffffff"
        width: 50
        text: qsTr("Total")

        anchors.top: parent.top

        anchors.topMargin: 10

        anchors.left: parent.horizontalCenter
        anchors.leftMargin: 8

        font.pixelSize: 16
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Text {
        id: goal
        width: 50

        x: ((total.x + total.width) + (amountLeft.x - amountLeft.width / 2.)) / 2.
        color: "#ffffff"
        text: qsTr("Goal")
        anchors.verticalCenter: total.verticalCenter

        font.pixelSize: 16
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Text {
        id: amountLeft
        width: 76
        color: "#ffffff"
        text: qsTr("Left")

        anchors.verticalCenter: total.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 15
        font.pixelSize: 16
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
}
