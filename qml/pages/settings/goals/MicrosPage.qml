import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

BaseSettingsTab {
    id: micros

    title: "Additional Goals"

    color: Constants.bg

    ScrollView {
        contentWidth: -1 //parent.width - 20
        anchors {
            top: nav.bottom
            bottom: parent.bottom
            right: parent.right
            left: parent.left

            topMargin: 25 * Constants.scalar
        }

        Component.onCompleted: contentHeight += 50 * Constants.scalar

        onHeightChanged: contentHeight += 50 * Constants.scalar

        ColumnLayout {
            uniformCellSizes: true
            spacing: 25 * Constants.scalar

            anchors.fill: parent
            anchors.topMargin: 25 * Constants.scalar
            anchors.rightMargin: 20

            // TODO: implement real suffixes
            GoalSpinBox {
                Layout.fillWidth: true
                label: "Saturated Fat (g)"
                key: "satFat"
                defaultValue: 50

                stepSize: 5
            }

            GoalSpinBox {
                Layout.fillWidth: true
                label: "Polyunsatured Fat (g)"
                key: "polyFat"
                defaultValue: 0

                stepSize: 5
            }

            GoalSpinBox {
                Layout.fillWidth: true
                label: "Monounsaturated Fat (g)"
                key: "monoFat"
                defaultValue: 50

                stepSize: 5
            }

            GoalSpinBox {
                Layout.fillWidth: true
                label: "Trans Fat (g)"
                key: "transFat"
                defaultValue: 0

                stepSize: 5
            }

            GoalSpinBox {
                Layout.fillWidth: true
                label: "Cholesterol (mg)"
                key: "cholesterol"
                defaultValue: 600

                stepSize: 10
            }

            GoalSpinBox {
                Layout.fillWidth: true
                label: "Sodium (mg)"
                key: "sodium"
                defaultValue: 6000

                stepSize: 100
            }

            GoalSpinBox {
                Layout.fillWidth: true
                label: "Potassium (mg)"
                key: "potassium"
                defaultValue: 4000

                stepSize: 100
            }

            GoalSpinBox {
                Layout.fillWidth: true
                label: "Fiber (g)"
                key: "fiber"
                defaultValue: 20

                stepSize: 5
            }

            GoalSpinBox {
                Layout.fillWidth: true
                label: "Sugar (g)"
                key: "sugar"
                defaultValue: 100

                stepSize: 5
            }

            GoalSpinBox {
                Layout.fillWidth: true
                label: "Vitamin A (% DV)"
                key: "vitaminA"
                defaultValue: 100

                stepSize: 10
            }

            GoalSpinBox {
                Layout.fillWidth: true
                label: "Vitamin C (% DV)"
                key: "vitaminC"
                defaultValue: 100

                stepSize: 10
            }

            GoalSpinBox {
                Layout.fillWidth: true
                label: "Calcium (% DV)"
                key: "calcium"
                defaultValue: 100

                stepSize: 10
            }

            GoalSpinBox {
                Layout.fillWidth: true
                label: "Iron (% DV)"
                key: "iron"
                defaultValue: 100

                stepSize: 10
            }
        }
    }
}
