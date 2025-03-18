import QtQuick
import QtQuick.Controls

import OpenFitnessPal

AnimatedDialog {
    id: msg

    required property string text

    width: 300 * Constants.scalar

    standardButtons: Dialog.Ok

    Text {
        id: txt

        anchors.fill: parent
        anchors.margins: 10 * Constants.scalar

        font.pixelSize: 16 * Constants.scalar
        color: Constants.text

        text: msg.text
    }
}
