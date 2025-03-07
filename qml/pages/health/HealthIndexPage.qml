import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

Rectangle {
    signal markers
    signal symptoms

    id: initial

    color: Constants.bg

    ColumnLayout {
        spacing: 15 * Constants.scalar
        anchors {
            top: parent.top
            right: parent.right
            left: parent.left
        }

        BigButton {
            name: "Markers"
            onClicked: initial.markers()
        }

        BigButton {
            name: "Symptoms"
            onClicked: initial.symptoms()
        }
    }
}
