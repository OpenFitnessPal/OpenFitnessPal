import QtQuick
import QtQuick.Controls
import QtQuick.Layouts 6.6

import OpenFitnessPal

Rectangle {
    id: food

    color: Constants.bg

    Text {
        color: Constants.text
        font.pixelSize: 25 * Constants.scalar

        text: "Food Page"
        anchors.centerIn: parent
    }
}
