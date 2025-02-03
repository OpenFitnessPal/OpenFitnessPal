import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

BaseSettingsTab {
    id: micros

    title: "Additional Goals"

    color: Constants.bg

    // ScrollView {
    //     contentWidth: -1 //parent.width - 20
    //     anchors {
    //         top: nav.bottom
    //         bottom: parent.bottom
    //         right: parent.right
    //         left: parent.left

    //         topMargin: 25 * Constants.scalar
    //     }

    //     Component.onCompleted: contentHeight += 50 * Constants.scalar

    //     onHeightChanged: contentHeight += 50 * Constants.scalar
    ColumnLayout {
        uniformCellSizes: true
        spacing: 0

        anchors {
            top: nav.bottom
            right: parent.right
            left: parent.left

            topMargin: 25 * Constants.scalar
        }

        GoalField {
            Layout.fillWidth: true
            label: "Saturated Fat"
            key: "satFat"
            defaultValue: 50

            suffix: "g"
        }

        GoalField {
            Layout.fillWidth: true
            label: "Polyunsatured Fat"
            key: "polyFat"
            defaultValue: 0

            suffix: "g"
        }

        GoalField {
            Layout.fillWidth: true
            label: "Monounsaturated Fat"
            key: "monoFat"
            defaultValue: 50

            suffix: "g"
        }

        GoalField {
            Layout.fillWidth: true
            label: "Trans Fat"
            key: "transFat"
            defaultValue: 0

            suffix: "g"
        }

        GoalField {
            Layout.fillWidth: true
            label: "Cholesterol"
            key: "cholesterol"
            defaultValue: 600

            suffix: "mg"
        }

        GoalField {
            Layout.fillWidth: true
            label: "Sodium"
            key: "sodium"
            defaultValue: 6000

            to: 99999

            suffix: "mg"
        }

        GoalField {
            Layout.fillWidth: true
            label: "Potassium"
            key: "potassium"
            defaultValue: 4000

            to: 99999

            suffix: "mg"
        }

        GoalField {
            Layout.fillWidth: true
            label: "Fiber"
            key: "fiber"
            defaultValue: 20

            suffix: "g"
        }

        GoalField {
            Layout.fillWidth: true
            label: "Sugar"
            key: "sugar"
            defaultValue: 100

            suffix: "g"
        }

        GoalField {
            Layout.fillWidth: true
            label: "Vitamin A"
            key: "vitaminA"
            defaultValue: 100

            suffix: "% DV"
        }

        GoalField {
            Layout.fillWidth: true
            label: "Vitamin C"
            key: "vitaminC"
            defaultValue: 100

            suffix: "% DV"
        }

        GoalField {
            Layout.fillWidth: true
            label: "Calcium"
            key: "calcium"
            defaultValue: 100

            suffix: "% DV"
        }

        GoalField {
            Layout.fillWidth: true
            label: "Iron"
            key: "iron"
            defaultValue: 100

            suffix: "% DV"
        }
    }
    // }
}
