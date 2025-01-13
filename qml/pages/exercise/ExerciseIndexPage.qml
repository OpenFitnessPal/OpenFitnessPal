import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

Rectangle {
    signal routines
    signal exercises

    id: initial

    color: Constants.bg

    ColumnLayout {
        spacing: 15 * Constants.scalar
        anchors {
            top: parent.top
            right: parent.right
            left: parent.left
        }

        SettingsButton {
            name: "Routines"
            onClicked: initial.routines()
        }

        SettingsButton {
            name: "Exercise"
            onClicked: initial.exercises()
        }
    }
}
