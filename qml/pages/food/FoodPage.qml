import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

Rectangle {
    property date currentDate

    function back() {
        if (stack.depth > 1) {
            stack.pop()
            return true
        }

        return false
    }

    id: food

    color: Constants.bg

    BetterStackView {
        id: stack
        initialItem: foodTab

        anchors {
            top: parent.top
            bottom: parent.bottom
            left: parent.left
            right: parent.right

            topMargin: 10 * Constants.scalar
        }

        FoodTab {
            id: foodTab
            visible: false

            onSearch: mealNumber => {
                          foodSearch.mealNumber = mealNumber
                          console.log(mealNumber, foodSearch.mealNumber)
                          stack.push(foodSearch)
                      }

            onEdit: serving => {
                        foodEdit.serving = serving
                        stack.push(foodEdit)
                    }
        }

        FoodSearch {
            id: foodSearch
            visible: false

            onAdd: (mealNumber, serving) => {
                       foodTab.add(mealNumber, serving)
                       stack.pop()
                   }
        }

        FoodEdit {
            id: foodEdit
            visible: false
        }
    }
}
