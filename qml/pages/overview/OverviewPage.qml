import QtQuick
import QtQuick.Controls
import QtQuick.Layouts 6.6

import OpenFitnessPal

Rectangle {
    property date currentDate

    function back() {}

    id: overview

    color: Constants.bg

    Text {
        color: Constants.text
        font.pixelSize: Math.round(25 * Constants.scalar)

        text: "Overview Page"
        anchors.centerIn: parent
    }
}
