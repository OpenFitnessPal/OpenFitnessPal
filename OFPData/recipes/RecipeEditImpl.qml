import QtQuick 2.15

import OFPNative
import OFPData

RecipeEditForm {
    width: parent.width
    height: parent.height

    FoodServingModel {
        id: fsm
    }

    signal ready(var recipe)

    property var recipe

    recipeName.text: recipe.name

    servings.onValueChanged: {
        recipe.servings = servings.value / 100.0
    }

    function loadData() {
        fsm.clear()
        servings.value = recipe.servings * 100

        fsm.add(recipe.foods)
    }

    add.onClicked: {
        search.food.opening()
        search.open()
        search.food.searchReady.connect(addFood)
    }

    calories.text: Math.round(recipe.nutrients().calories * 10) / 10.
    carbs.text: Math.round(recipe.nutrients().carbs * 10) / 10.
    fat.text: Math.round(recipe.nutrients().fat * 10) / 10.
    protein.text: Math.round(recipe.nutrients().protein * 10) / 10.

    listView.model: fsm
    listView.delegate: FoodServingInfoImpl {
        clip: true
        function editEntry(item, serving, units) {
            model.units = units
            model.servingSize = serving

            recipe.foods = fsm.foods

            resetNutrients()

            foodEdit.edit.ready.disconnect(editEntry)
        }

        mouse.onClicked: {
            foodEdit.edit.foodServing = serving

            foodEdit.edit.loadData()
            foodEdit.open()

            foodEdit.edit.ready.connect(editEntry)
        }

        onDeleteFood: {
            fsm.removeRow(foodID)

            recipe.foods = fsm.foods
            resetNutrients()
        }

        remove.visible: true
    }

    function resetNutrients() {
        calories.text =  Math.round(recipe.nutrients().calories * 10) / 10.
        carbs.text = Math.round(recipe.nutrients().carbs * 10) / 10.
        fat.text = Math.round(recipe.nutrients().fat * 10) / 10.
        protein.text = Math.round(recipe.nutrients().protein * 10) / 10.
    }

    function addFood(servings) {
        search.food.searchReady.disconnect(addFood)

        fsm.add(servings);
        fsm.cache(servings)

        recipe.foods = fsm.foods
        resetNutrients()
    }
}
