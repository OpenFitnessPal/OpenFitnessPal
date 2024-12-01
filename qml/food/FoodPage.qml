import QtQuick 2.15
import QtQuick.Controls 2.15

FoodPageForm {
    function reloadData() {
        swipe.currentItem.reloadData(currentDate)
    }

    function setDate(date) {
        journal.reloadData(date)
        nutrition.reloadData(date)
    }

    function reloadMealNames() {
        journal.reloadMealNames()
    }

    swipe.onCurrentItemChanged: reloadData()
    journal.onNutritionInfoRequested: swipe.setCurrentIndex(1)
    nutrition.onCloseOut: swipe.setCurrentIndex(0)
}
