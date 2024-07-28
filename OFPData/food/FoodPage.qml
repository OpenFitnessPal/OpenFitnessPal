import QtQuick 2.15
import QtQuick.Controls 2.15

FoodPageForm {
    function reloadData() {
        swipe.currentItem.reloadData(currentDate)
    }

    swipe.onCurrentItemChanged: reloadData()
    journal.calPreview.onClicked: swipe.setCurrentIndex(1)
}
