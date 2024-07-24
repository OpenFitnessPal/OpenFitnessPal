import QtQuick 2.15

import OFPTest

ExerciseForm {
    id: exercise

    width: parent.width

    signal changed()

    property alias esm: esm

    ExerciseSetsModel {
        id: esm
    }

    function setData(sets) {
        esm.setData(sets)
    }

    function addSet(reps: int, weight: int) {
        esm.add(reps, weight)
        exercise.changed()
    }

    function setName(newName: string) {
        name = newName
        exerciseName.text = newName
        exercise.changed()
    }

    remove.onClicked: deleteMe(exID)

    add.onClicked: {
        esm.duplicateLast()
        exercise.changed()
    }

    listView.delegate: ExerciseSetImpl {
        id: set
        clip: true

        onDeleteSet: {
            esm.removeRow(setID)
            exercise.changed()
        }

        onChanged: (reps, weight, id) =>
                   {
                       model.reps = reps
                       model.weight = weight

                       exercise.changed()
                   }

        Component.onCompleted: {
            repsEdit.value = model.reps
            weightEdit.value = model.weight

            weightEdit.valueChanged.connect(changeData)
            repsEdit.valueChanged.connect(changeData)

            exercise.changed()
        }
    }

    exerciseName.onEditingFinished: {
        setName(exerciseName.displayText)
        exercise.changed()
    }
}
