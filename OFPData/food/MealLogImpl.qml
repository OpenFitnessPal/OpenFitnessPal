import QtQuick 2.15
import QtQuick.Controls

import OFPNative

MealLogForm {
    signal nutritionUpdated

    id: impl
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

    Component.onCompleted: {
        reloadData()
    }

    listView.model: fsm
    listView.delegate: FoodServingInfoImpl {
        function editEntry(servings) {
            foodEdit.edit.ready.disconnect(editEntry)

            let food = servings[0]
            model.serving = food
            model.servingSize = food.size

            fsm.saveData(currentDate)
            nutritionUpdated()
        }

        mouse.onClicked: {
            foodEdit.edit.foodServing = model.serving
            console.log("Serving size unit " + foodEdit.edit.foodServing.size.unit())

            foodEdit.edit.loadData()
            foodEdit.open()

            foodEdit.edit.ready.connect(editEntry)
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
        if (!servings[0].isRecipe) fsm.cache(servings)

        fsm.saveData(currentDate)
        nutritionUpdated()
    }
}
