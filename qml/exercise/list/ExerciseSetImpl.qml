import QtQuick 2.15

ExerciseSetForm {
    id: exerciseSet
    width: parent.width

    remove.onClicked: exerciseSet.deleteSet(setID)

    function changeData() {
        reps = repsEdit.value
        weight = weightEdit.value

        exerciseSet.changed(repsEdit.value, weightEdit.value, setID)
    }
}
