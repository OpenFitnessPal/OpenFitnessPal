import QtQuick 2.15

FoodServingInfoForm {
    width: parent.width

    signal ready(var servings)

    property int meal

    foodName.text: item.name

    brandServing.text: item.brand + ", " + servingSize.unit(units)

    calories.text: Math.round(item.nutrients.calories * servingSize.multiplier(units) * 10) / 10. + "kcal"

    function send(servings) {
        foodEdit.edit.ready.disconnect(send)
        ready(servings)
    }

    remove.onClicked: deleteFood(foodID)
}
