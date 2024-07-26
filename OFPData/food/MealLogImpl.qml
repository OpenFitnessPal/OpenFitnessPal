import QtQuick 2.15
import QtQuick.Controls

import OFPNative

MealLogForm {
    id: impl
    width: parent.width
    // height: Layout.height
    // clip: true

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
        }

        mouse.onClicked: {
            foodEdit.edit.foodServing = serving

            foodEdit.edit.loadData()
            foodEdit.open()

            foodEdit.edit.ready.connect(editEntry)
        }

        onDeleteFood: {
            fsm.removeRow(foodID)
            fsm.saveData(currentDate)
        }

        remove.visible: true
    }
    listView.clip: true

    function addFood(servings) {
        search.food.searchReady.disconnect(addFood)

        fsm.add(servings);
        fsm.cache(servings)

        fsm.saveData(currentDate)
    }
}
