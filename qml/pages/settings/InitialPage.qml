import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

Rectangle {
    signal meals
    signal search
    signal goals

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
            id: meals
            name: "Meals"
            onClicked: initial.meals()
        }

        SettingsButton {
            id: search
            name: "Search"
            onClicked: initial.search()
        }

        SettingsButton {
            id: goals
            name: "Goals"
            onClicked: initial.goals()
        }
    }
}
