import QtQuick
import QtQuick.Controls
import QtQuick.Shapes
import QtQuick.Layouts

import OpenFitnessPal

BaseTab {
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

    property var recipe: null

    property double carbs: recipe !== null ? (Math.round(
                                                  recipe.nutrients.carbs * 10.) / 10.) : 0.0
    property double fat: recipe !== null ? (Math.round(
                                                recipe.nutrients.fat * 10.) / 10.) : 0.0
    property double protein: recipe !== null ? (Math.round(
                                                    recipe.nutrients.protein * 10.) / 10.) : 0.0

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

    FoodModel {
        id: fm
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

            FoodMacroGraph {
                id: graph

                calories: recipeEdit.calories
                percents: recipeEdit.percents
                values: recipeEdit.values
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
