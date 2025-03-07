import QtQuick
import QtQuick.Controls
import QtQuick.Shapes
import QtQuick.Layouts

import OpenFitnessPal

BaseTab {
    signal dataChanged

    id: foodEdit

    property var serving: null

    property double carbs: serving !== null ? (Math.round(
                                                   serving.size.multiplier(
                                                       serving.units) * serving.item.nutrients.carbs
                                                   * 10.) / 10.) : 0.0
    property double fat: serving !== null ? (Math.round(
                                                 serving.size.multiplier(
                                                     serving.units) * serving.item.nutrients.fat
                                                 * 10.) / 10.) : 0.0
    property double protein: serving !== null ? (Math.round(
                                                     serving.size.multiplier(
                                                         serving.units)
                                                     * serving.item.nutrients.protein
                                                     * 10.) / 10.) : 0.0

    property double carbCalories: carbs * 4.0
    property double fatCalories: fat * 9.0
    property double proteinCalories: protein * 4.0

    property double calories: carbCalories + fatCalories + proteinCalories

    /** Data for Macro Display */

    // Carbs, fat, protein values
    property list<double> values: [carbs, fat, protein]

    // Carbs, fat, protein as percentages of the total calorie makeup
    property list<double> percents: [//.
        Math.round(carbCalories / calories * 100.0), //.
        Math.round(fatCalories / calories * 100.0), //.
        Math.round(proteinCalories / calories * 100.0) //.
    ]

    ServingSizeModel {
        id: fsm
    }

    onServingChanged: {
        fsm.clear()
        if (serving !== null && serving.name !== "") {
            fsm.add(serving.item.servingSizes)
        }
    }

    title: "Edit Serving"

    ServingSizeDialog {
        id: servingDialog
        model: fsm

        onSelect: selection => {
                      serving.size = selection
                      dataChanged()
                  }
    }

    ColumnLayout {
        spacing: 0
        anchors {
            top: nav.bottom
            left: parent.left
            right: parent.right

            topMargin: 10 * Constants.scalar
        }

        UnlabeledTextField {
            id: name

            bindTarget: serving
            bindedProperty: "name"

            font.pixelSize: 22 * Constants.scalar
            font.bold: true

            background: Item {}

            Layout.fillWidth: true

            onTextEdited: dataChanged()
        }

        LabeledNumberField {
            Layout.fillWidth: true

            label: "Servings"
            suffix: ""

            bindTarget: serving
            bindedProperty: "units"

            onValueChanged: dataChanged()
        }

        Rectangle {
            signal clicked

            Layout.fillWidth: true

            id: combo

            color: Constants.sub

            implicitHeight: 45 * Constants.scalar

            MouseArea {
                anchors.fill: parent
                onClicked: servingDialog.open()

                RowLayout {
                    anchors {
                        fill: parent

                        rightMargin: 10 * Constants.scalar
                    }

                    Text {
                        Layout.fillWidth: true
                        Layout.leftMargin: 15 * Constants.scalar

                        color: Constants.text

                        text: "Serving Size"

                        font.pixelSize: 16 * Constants.scalar
                    }

                    Text {
                        color: Constants.accent

                        text: serving !== null ? serving.size.unit(
                                                     1) : "1 Serving"

                        font.pixelSize: 16 * Constants.scalar
                    }
                }
            }
        }

        FoodMacroGraph {
            id: graph
            calories: foodEdit.calories
            percents: foodEdit.percents
            values: foodEdit.values
        }
    }
}
