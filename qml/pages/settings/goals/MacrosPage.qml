import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

BaseSettingsTab {
    id: macros

    title: "Macronutrient Goals"

    color: Constants.bg

    nav.onClicked: {
        if (valid.text === "100%") {
            carbs.accept()
            fat.accept()
            protein.accept()
        }
    }

    function recalc() {
        carbs.recalc()
        fat.recalc()
        protein.recalc()
    }

    MacroPresetDialog {
        id: macroPresets

        onResetGoal: (c, f, p) => {
                         if (c !== 0) {
                             carbs.value = c
                             fat.value = f
                             protein.value = p
                         }
                     }
    }

    Button {
        id: button
        font.pixelSize: 25 * Constants.scalar

        anchors {
            left: parent.left
            right: parent.right

            top: nav.bottom

            margins: 8 * Constants.scalar
        }

        text: "Macro Presets"
        onClicked: macroPresets.open()

        background: Rectangle {
            color: button.pressed ? Constants.accentPressed : Constants.accent
            radius: 5 * Constants.scalar
        }
    }

    RowLayout {
        id: editor
        uniformCellSizes: true

        spacing: 80 * Constants.scalar

        anchors {
            top: button.bottom
            bottom: notice.top
            horizontalCenter: parent.horizontalCenter

            topMargin: 10 * Constants.scalar
        }

        MacroGoal {
            id: carbs
            Layout.fillWidth: true
            Layout.preferredHeight: 550 * Constants.scalar
            label: "Carbs"

            key: "carbs"
            defaultValue: 35
            handleColor: "lightblue"
        }

        MacroGoal {
            id: fat
            Layout.fillWidth: true
            Layout.preferredHeight: 550 * Constants.scalar
            label: "Fat"

            key: "fat"
            caloriesPerGram: 9
            defaultValue: 35

            handleColor: "#9500ff"
        }

        MacroGoal {
            id: protein
            Layout.fillWidth: true
            Layout.preferredHeight: 550 * Constants.scalar
            label: "Protein"

            key: "protein"
            defaultValue: 30
            handleColor: "yellow"
        }
    }

    Rectangle {
        id: notice
        color: Constants.button

        implicitHeight: 75 * Constants.scalar

        anchors {
            bottom: parent.bottom
            left: parent.left
            right: parent.right

            margins: 8 * Constants.scalar
        }

        GridLayout {
            rows: 2
            columns: 2

            anchors.fill: parent
            anchors.margins: 12 * Constants.scalar

            Text {
                font.pixelSize: 22 * Constants.scalar
                color: Constants.text

                text: "% Total"
            }

            Text {
                id: valid
                font.pixelSize: 22 * Constants.scalar
                color: text === "100%" ? "lightgreen" : "red"

                text: (carbs.value + fat.value + protein.value) + "%"
            }

            Text {
                font.pixelSize: 16 * Constants.scalar
                color: "#A0A0A0"

                text: "Macronutrients must equal 100%"
            }
        }
    }
}
