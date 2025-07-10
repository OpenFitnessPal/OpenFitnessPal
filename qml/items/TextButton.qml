import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

Rectangle {
    id: bigButton

    signal clicked

    required property string name
    property int fontSize: 18

    color: Constants.button

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
