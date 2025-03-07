import QtQuick
import QtQuick.Controls
import QtQuick.Shapes
import QtQuick.Layouts

import OpenFitnessPal

BaseSettingsTab {
    signal edit(var recipe)
    signal search

    function setRecipe(newRecipe) {
        fm.foods = newRecipe.foods
        recipe = newRecipe
    }

    function add(servings) {
        fm.add(servings)

        recipe.foods = fm.foods
    }

    function updateServing() {
        if (recipe === null)
            return
        recipe.foods = fm.foods

        carbs = Math.round(recipe.nutrients.carbs * 10.) / 10.
        fat = Math.round(recipe.nutrients.fat * 10.) / 10.
        protein = Math.round(recipe.nutrients.protein * 10.) / 10.
    }

    onRecipeChanged: updateServing()

    id: recipeEdit

    property var recipe: {
        "name": "",
        "servings": 0,
        "foods": [],
        "nutrients": {
            "carbs": 0,
            "fat": 0,
            "protein": 0
        },
        "recipe": {}
    }

    property double carbs: Math.round(recipe.nutrients.carbs * 10.) / 10.
    property double fat: Math.round(recipe.nutrients.fat * 10.) / 10.
    property double protein: Math.round(recipe.nutrients.protein * 10.) / 10.

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

    // labels for the macro display
    property list<string> labels: ["Carbs", "Fat", "Protein"]
    property list<color> colors: ["lightblue", "#9500ff", "yellow"]

    FoodModel {
        id: fm

        // onFoodsChanged: recipe.foods = foods
    }

    title: "Edit Recipe"

    ScrollView {
        id: scroll

        anchors {
            top: nav.bottom

            topMargin: 10 * Constants.scalar
        }

        width: parent.width
        height: parent.height - anchors.topMargin

        contentWidth: parent.width - effectiveScrollBarWidth

        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

        ColumnLayout {
            spacing: 0

            anchors.fill: parent

            UnlabeledTextField {
                id: name

                bindTarget: recipe
                bindedProperty: "name"

                font.pixelSize: 22 * Constants.scalar
                font.bold: true

                background: Item {}

                Layout.fillWidth: true
            }

            LabeledNumberField {
                id: serv

                Layout.fillWidth: true

                label: "Servings"
                suffix: ""

                bindTarget: recipe
                bindedProperty: "servings"
            }

            // TODO: Extract this
            RowLayout {
                id: graph
                uniformCellSizes: true
                Layout.fillWidth: true

                Layout.margins: 10 * Constants.scalar

                Layout.preferredHeight: 90 * Constants.scalar

                Item {
                    Layout.fillHeight: true
                    Layout.preferredWidth: 90 * Constants.scalar

                    Shape {
                        id: shape
                        anchors.centerIn: parent
                        width: Math.min(parent.width, parent.height) * 0.8
                        height: width

                        property double stroke: 10 * Constants.scalar

                        ShapePath {
                            id: carbPath

                            strokeColor: colors[0]
                            strokeWidth: shape.stroke
                            fillColor: "transparent"

                            startX: shape.width / 2
                            startY: 0

                            PathAngleArc {
                                id: carbArc

                                centerX: shape.width / 2
                                centerY: centerX

                                radiusX: centerX
                                radiusY: centerX

                                startAngle: -90
                                sweepAngle: carbCalories / calories * 360.0
                            }
                        }

                        ShapePath {
                            id: fatPath

                            strokeColor: colors[1]
                            strokeWidth: shape.stroke
                            fillColor: "transparent"

                            startX: shape.width / 2
                            startY: 0

                            PathAngleArc {
                                id: fatArc

                                centerX: shape.width / 2
                                centerY: centerX

                                radiusX: centerX
                                radiusY: centerX

                                startAngle: carbArc.startAngle + carbArc.sweepAngle
                                sweepAngle: fatCalories / calories * 360.0
                            }
                        }

                        ShapePath {
                            id: proteinPath

                            strokeColor: colors[2]
                            strokeWidth: shape.stroke
                            fillColor: "transparent"

                            startX: shape.width / 2
                            startY: 0

                            PathAngleArc {
                                centerX: shape.width / 2
                                centerY: centerX

                                radiusX: centerX
                                radiusY: centerX

                                startAngle: fatArc.startAngle + fatArc.sweepAngle
                                sweepAngle: proteinCalories / calories * 360.0
                            }
                        }
                    }

                    Text {
                        anchors.centerIn: parent
                        text: Math.round(calories)
                        color: Constants.text

                        width: 60 * Constants.scalar

                        fontSizeMode: Text.Fit

                        font {
                            bold: true
                            pixelSize: 20 * Constants.scalar
                        }

                        horizontalAlignment: Text.AlignHCenter
                    }
                }

                Repeater {
                    model: 3

                    ColumnLayout {
                        Layout.fillHeight: true
                        // Layout.fillWidth: true
                        Layout.alignment: Qt.AlignCenter

                        Text {
                            Layout.fillWidth: true

                            color: colors[index]
                            text: (isNaN(
                                       percents[index]) ? 0 : percents[index]) + "%"

                            font.pixelSize: 14 * Constants.scalar
                            horizontalAlignment: Text.AlignHCenter
                        }

                        Text {
                            Layout.fillWidth: true

                            color: Constants.text
                            text: (isNaN(
                                       values[index]) ? 0 : values[index]) + "g"

                            font.pixelSize: 18 * Constants.scalar
                            horizontalAlignment: Text.AlignHCenter
                        }

                        Text {
                            Layout.fillWidth: true

                            color: Constants.text
                            text: labels[index]

                            font.pixelSize: 14 * Constants.scalar
                            horizontalAlignment: Text.AlignHCenter
                        }
                    }
                }
            }

            RowLayout {
                id: header

                implicitHeight: 60 * Constants.scalar

                Layout.fillWidth: true

                Text {
                    Layout.fillWidth: true

                    text: "Foods"
                    color: Constants.text

                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 22 * Constants.scalar
                    font.bold: true
                }

                NavButton {
                    label: "Add"
                    onClicked: recipeEdit.search()
                }
            }

            FoodView {
                foods: fm
                interactive: false

                clip: false
                Layout.fillHeight: true

                onEdit: recipe => recipeEdit.edit(recipe)
                onFoodRemoved: recipeEdit.updateServing()
            }
        }
    }
}
