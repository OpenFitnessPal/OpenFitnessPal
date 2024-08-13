import QtQuick 2.15

ExerciseRootPageForm {
    function reloadData() {
        swipe.currentItem.reloadData(currentDate)
    }

    function setDate(date) {
        exercises.reloadData(date)
        routines.reloadData(date)
    }

    function reloadMealNames() {
        exercises.reloadMealNames()
    }

    swipe.onCurrentItemChanged: reloadData()
    exercises.onRoutinesRequested: swipe.setCurrentIndex(1)
    routines.onCloseOut: swipe.setCurrentIndex(0)
}
