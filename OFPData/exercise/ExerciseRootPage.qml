import QtQuick 2.15

ExerciseRootPageForm {
    function reloadData() {
        exercises.reloadData(currentDate)
    }

    function setDate(date) {
        exercises.reloadData(date)
    }

    function reloadMealNames() {
        exercises.reloadMealNames()
    }

    swipe.onCurrentItemChanged: reloadData()
    exercises.onRoutinesRequested: swipe.setCurrentIndex(1)
    routines.onCloseOut: swipe.setCurrentIndex(0)
    routines.onEditRoutine: (id, routine) => {
                                routineEdit.reload(id, routine)
                                swipe.setCurrentIndex(2)
                            }

    
    routineEdit.onAddRoutine: swipe.setCurrentIndex(0)
    routineEdit.onCloseOut: swipe.setCurrentIndex(1)

    routineEdit.onChanged: {
                               routines.setRoutine(routineEdit.id, routineEdit.routine)
                               routines.save()
                           }
}
