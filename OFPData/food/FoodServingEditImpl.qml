import QtQuick 2.15
import QtQuick.Controls 2.15

import OFPNative

FoodServingEditForm {
    width: parent.width
    height: parent.height

    FoodServingComboBoxModel {
        id: fsm
    }

    signal ready(var servings)

    property var foodServing

    foodName.text: foodServing.item.name

    unit.model: fsm
    unit.textRole: "name"
    unit.valueRole: "size"

    function resetMacros() {
        calories.text = Math.round(foodServing.size.multiplier(servings.value / 100.0) * foodServing.item.nutrients.calories * 10.) / 10.
        carbs.text = Math.round(foodServing.size.multiplier(servings.value / 100.0) * foodServing.item.nutrients.carbs * 10.) / 10.
        fat.text = Math.round(foodServing.size.multiplier(servings.value / 100.0) * foodServing.item.nutrients.fat * 10.) / 10.
        protein.text = Math.round(foodServing.size.multiplier(servings.value / 100.0) * foodServing.item.nutrients.protein * 10.) / 10.
    }

    unit.onCurrentIndexChanged: {
        foodServing.size = unit.valueAt(unit.currentIndex)
        resetMacros()
    }

    servings.onValueChanged: {
        foodServing.units = servings.value / 100.0
        resetMacros()
    }

    function loadData() {
        let index = fsm.indexOf(foodServing.size)
        console.log("LoadData pre-clear servingsize unit " + foodServing.size.unit());
        fsm.clear()
        console.log("LoadData postclear servingsize unit " + foodServing.size.unit());
        fsm.add(foodServing.item.servingSizes)
        console.log("LoadData post add servingsize unit " + foodServing.size.unit());

        servings.value = foodServing.units * 100.0
        unit.currentIndex = fsm.indexOf(foodServing.size);

        console.log(unit.currentIndex + " " + unit.indexOfValue(foodServing.size))

        resetMacros()
    }

    calories.text: Math.round(unit.currentValue.multiplier(servings.realValue) * foodServing.item.nutrients.calories * 10.) / 10.
    carbs.text: Math.round(unit.currentValue.multiplier(servings.realValue) * foodServing.item.nutrients.carbs * 10.) / 10.
    fat.text: Math.round(unit.currentValue.multiplier(servings.realValue) * foodServing.item.nutrients.fat * 10.) / 10.
    protein.text: Math.round(unit.currentValue.multiplier(servings.realValue) * foodServing.item.nutrients.protein * 10.) / 10.
}
