import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

Rectangle {
    id: bigButton

    signal clicked

    required property string name

    color: Constants.button

    Layout.fillWidth: true
    Layout.preferredHeight: 40 * Constants.scalar
    Layout.alignment: Qt.AlignTop

    MouseArea {
        hoverEnabled: true
        onHoveredChanged: parent.color
                          = containsMouse ? Constants.buttonHighlighted : Constants.button

        onClicked: parent.clicked()

        anchors.fill: parent

        Text {
            anchors {
                fill: parent
            }

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            font.pixelSize: Math.round(18 * Constants.scalar)
            color: Constants.text
            text: name
        }
    }
}
