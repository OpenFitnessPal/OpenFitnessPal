import QtQuick
import QtQuick.Controls
import QtQuick.Layouts 6.6

import OpenFitnessPal

Rectangle {
    function back() {}

    id: overview

    color: Constants.bg

    BetterStackView {
        id: stack
        initialItem: recipeTab

        anchors {
            top: parent.top
            bottom: parent.bottom
            left: parent.left
            right: parent.right

            topMargin: 10 * Constants.scalar
        }

        FoodEdit {
            id: foodEdit
            visible: false

            onDataChanged: recipeEdit.updateServing()
        }

        RecipeEdit {
            id: recipeEdit
            visible: false

            onEdit: serving => {
                        foodEdit.serving = serving
                        stack.push(foodEdit)
                    }

            onSearch: stack.push(foodSearch)

            onGoingBack: recipeTab.reload()
        }

        RecipeTab {
            id: recipeTab

            onEdit: recipe => {
                        recipeEdit.setRecipe(recipe)
                        stack.push(recipeEdit)
                    }
        }

        FoodSearch {
            id: foodSearch
            visible: false

            onAdd: (_, serving) => {
                       recipeEdit.add(serving)
                       recipeEdit.updateServing()
                       stack.pop()
                   }
        }
    }
}
