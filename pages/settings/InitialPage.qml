import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OFPItems

Rectangle {
    signal meals
    signal search
    signal goals

    id: initial

    color: Constants.bg

    ColumnLayout {
        spacing: 15
        anchors.fill: parent

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
