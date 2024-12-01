import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

import OpenFitnessPal

Rectangle {
    id: rectangle
    color: "#000000"

    signal removeRequested

    // width: 480
    height: 60

    property alias remove: remove

    RemoveButton {
        id: remove

        anchors.left: parent.left
        anchors.leftMargin: 20

        anchors.verticalCenter: parent.verticalCenter
    }

    Text {
        id: total
        color: "#ffffff"
        width: 50
        text: qsTr("Total")

        anchors.bottom: parent.bottom

        anchors.bottomMargin: 10

        anchors.left: parent.horizontalCenter
        anchors.leftMargin: 8

        font: Constants.mediumFont
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

        font: Constants.mediumFont
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
        font: Constants.mediumFont
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
}
