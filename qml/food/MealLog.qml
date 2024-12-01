import QtQuick 2.15
import QtQuick.Controls

import OpenFitnessPal

MealLogForm {
    signal nutritionUpdated

    width: parent.width

    add.onClicked: {
        search.food.opening()
        search.open()
        search.food.searchReady.connect(addFood)
    }

    FoodServingModel {
        id: fsm
        meal: mealNumber
    }

    function reloadData() {
        fsm.clear()
        fsm.loadData(currentDate)
    }

    function reloadMealName() {
        mealName.text = settings.get("meal" + mealNumber + "Name")
    }

    Component.onCompleted: {
        reloadData()
    }

    listView.model: fsm
    listView.delegate: FoodServingInfo {
        function removeConnection() {
            foodEdit.edit.ready.disconnect(editEntry)
        }

        function editEntry(servings) {
            removeConnection()

            let food = servings[0]
            model.serving = food
            model.servingSize = food.size

            fsm.saveData(currentDate)
            nutritionUpdated()
        }

        mouse.onClicked: {
            foodEdit.edit.foodServing = model.serving

            foodEdit.edit.loadData()
            foodEdit.open()

            foodEdit.edit.ready.connect(editEntry)
            foodEdit.rejected.connect(removeConnection)
        }

        onDeleteFood: {
            fsm.removeRow(foodID)
            fsm.saveData(currentDate)
            nutritionUpdated()
        }

        remove.visible: true
    }
    listView.clip: true

    function addFood(servings) {
        search.food.searchReady.disconnect(addFood)

        fsm.add(servings)
        if (!servings[0].isRecipe)
            fsm.cache(servings)

        fsm.saveData(currentDate)
        nutritionUpdated()
    }
}
