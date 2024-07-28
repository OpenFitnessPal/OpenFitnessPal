import QtQuick 2.15
import QtQuick.Controls 2.15

FoodPageForm {
    function reloadData() {
        swipe.currentItem.reloadData(currentDate)
    }

    swipe.onCurrentItemChanged: reloadData()
    journal.onNutritionInfoRequested: swipe.setCurrentIndex(1)
    nutrition.onCloseOut: swipe.setCurrentIndex(0)
}
