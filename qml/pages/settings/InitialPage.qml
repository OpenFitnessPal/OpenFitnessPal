import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

Rectangle {
    signal meals
    signal search
    signal goals
    signal dataButton

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
            name: "Meals"
            onClicked: initial.meals()
        }

        BigButton {
            name: "Search"
            onClicked: initial.search()
        }

        BigButton {
            name: "Goals"
            onClicked: initial.goals()
        }

        BigButton {
            name: "Data"
            onClicked: initial.dataButton()
        }
    }
}
