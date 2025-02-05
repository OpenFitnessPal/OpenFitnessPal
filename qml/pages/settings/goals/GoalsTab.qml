import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

BaseSettingsTab {
    property date currentDate

    onCurrentDateChanged: {
        weightManager.date = currentDate
        weight.value = weightManager.weight
    }

    signal macros
    signal micros

    id: goals

    title: "Goals"

    color: Constants.bg

    WeightGoalDialog {
        id: goalDialog

        onResetGoal: (idx, result) => {
                         goalManager.set("goal", idx)
                         calories.value = weight.value * (16 + idx * 2)
                         goal.text = result
                     }
    }

    ColumnLayout {
        spacing: 15 * Constants.scalar

        anchors {
            top: nav.bottom
            left: parent.left
            right: parent.right

            topMargin: 25 * Constants.scalar
        }

        ColumnLayout {
            Layout.fillWidth: true
            spacing: 0

            LabeledNumberField {
                id: weight

                Layout.fillWidth: true

                label: "Current Weight"
                suffix: "lbs"

                bindTarget: weightManager
                bindedProperty: "weight"
            }

            GoalField {
                id: calories

                Layout.fillWidth: true

                suffix: "kcal"
                label: "Calorie Target"

                key: "calories"
                defaultValue: 3000
            }

            Rectangle {
                signal clicked

                property list<string> goals: ["Fast Weight Loss", "Slow Weight Loss", "Maintain Weight", "Slow Weight Gain", "Fast Weight Gain"]
                property string text: this.goals[goalManager.get("goal", 2)]

                Layout.fillWidth: true

                id: goal

                color: Constants.sub

                implicitHeight: 45 * Constants.scalar

                MouseArea {
                    anchors.fill: parent
                    onClicked: goalDialog.open()

                    RowLayout {
                        anchors {
                            fill: parent

                            rightMargin: 10 * Constants.scalar
                        }

                        Text {
                            Layout.fillWidth: true
                            Layout.leftMargin: 15 * Constants.scalar

                            color: Constants.text

                            text: "Weight Goal"

                            font.pixelSize: 16 * Constants.scalar
                        }

                        Text {
                            color: Constants.accent

                            text: goal.text

                            font.pixelSize: 16 * Constants.scalar
                        }
                    }
                }
            }
        }

        SectionHeader {
            Layout.leftMargin: 15 * Constants.scalar
            Layout.fillWidth: true
            label: "Nutrition"
        }

        ColumnLayout {
            Layout.fillWidth: true
            spacing: 5 * Constants.scalar

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
        }

        SectionHeader {
            Layout.leftMargin: 15 * Constants.scalar
            Layout.fillWidth: true
            label: "Weekly Goals"
        }

        ColumnLayout {
            Layout.fillWidth: true
            spacing: 0

            GoalField {
                Layout.fillWidth: true
                label: "Workouts"
                suffix: "/ week"

                key: "workouts"
                defaultValue: 5
            }

            GoalField {
                Layout.fillWidth: true
                label: "Time per Workout"
                suffix: "min"

                key: "minutes"
                defaultValue: 120
            }
        }
    }
}
