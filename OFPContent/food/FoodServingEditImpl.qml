import QtQuick 2.15
import QtQuick.Controls 2.15

import OFPTest

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

    unit.onCurrentIndexChanged: {
        foodServing.size = unit.valueAt(unit.currentIndex)
    }

    servings.onValueChanged: foodServing.units = servings.value / 100.0

    function loadData() {
        fsm.clear()
        fsm.add(foodServing.item.servingSizes)

        servings.value = foodServing.units * 100.0
        unit.currentIndex = unit.indexOfValue(foodServing.size)
    }

    calories.text: Math.round(unit.currentValue.multiplier(servings.realValue) * foodServing.item.nutrients.calories * 10.) / 10.
    carbs.text: Math.round(unit.currentValue.multiplier(servings.realValue) * foodServing.item.nutrients.carbs * 10.) / 10.
    fat.text: Math.round(unit.currentValue.multiplier(servings.realValue) * foodServing.item.nutrients.fat * 10.) / 10.
    protein.text: Math.round(unit.currentValue.multiplier(servings.realValue) * foodServing.item.nutrients.protein * 10.) / 10.
}
