import QtQuick 2.15

ExerciseSetForm {
    id: exerciseSetImpl
    width: parent.width

    remove.onClicked: exerciseSetImpl.deleteSet(setID)

    function changeData() {
        reps = repsEdit.value
        weight = weightEdit.value

        exerciseSetImpl.changed(repsEdit.value, weightEdit.value, setID)
    }
}
