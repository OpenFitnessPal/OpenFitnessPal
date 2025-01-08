import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

BaseSettingsTab {
    signal macros
    signal micros

    id: goals

    title: "Goals"

    color: Constants.bg

    ColumnLayout {
        uniformCellSizes: true
        spacing: 20 * Constants.scalar

        anchors {
            top: nav.bottom
            left: parent.left
            right: parent.right

            margins: 8 * Constants.scalar
            topMargin: 25 * Constants.scalar
        }

        LabeledSpinBox {
            id: weight
            Layout.fillWidth: true
            label: "Weight (lbs)"

            editable: true

            bindedProperty: "weight"
            bindTarget: weightManager
        }

        GoalComboBox {
            Layout.fillWidth: true
            label: "Weight Goal"

            key: "goal"
            defaultValue: 2

            choices: ["Fast Weight Loss", "Slow Weight Loss", "Maintain Weight", "Slow Weight Gain", "Fast Weight Gain"]

            onActivated: index => {
                             let weightMultiplier = 16 + index * 2

                             // Fast Loss: 16
                             // Slow Loss: 18
                             // Maintain : 20
                             // Slow Gain: 22
                             // Fast Gain: 24
                             calories.value = weight.value * weightMultiplier
                         }
        }

        GoalSpinBox {
            id: calories
            Layout.fillWidth: true
            label: "Calories"

            editable: true
            stepSize: 100

            key: "calories"
            defaultValue: 3000
        }

        SectionHeader {
            Layout.fillWidth: true
            label: "Nutrition"
        }

        BetterButton {
            Layout.fillWidth: true
            name: "Macronutrient Goals"

            onClicked: macros()
        }

        BetterButton {
            Layout.fillWidth: true
            name: "Additional Nutrient Goals"

            onClicked: micros()
        }

        SectionHeader {
            Layout.fillWidth: true
            label: "Exercise"
        }

        GoalSpinBox {
            Layout.fillWidth: true
            label: "Workouts per Week"

            editable: true

            key: "workouts"
            defaultValue: 5
        }

        GoalSpinBox {
            Layout.fillWidth: true
            label: "Minutes per Workout"

            editable: true

            key: "minutes"
            defaultValue: 120

            stepSize: 10
        }
    }
}
