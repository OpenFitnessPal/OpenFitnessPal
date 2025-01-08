import QtQuick
import QtQuick.Controls
import QtQuick.Layouts 6.6

import OpenFitnessPal

Rectangle {
    id: exercisePage

    color: Constants.bg

    Text {
        color: Constants.text
        font.pixelSize: Math.round(25 * Constants.scalar)

        text: "Exercise Page"
        anchors.centerIn: parent
    }
}
