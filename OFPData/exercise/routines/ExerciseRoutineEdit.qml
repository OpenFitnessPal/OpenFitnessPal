import QtQuick 2.15

import OFPNative
import OFPData

ExerciseRoutineEditForm {
    id: impl
    signal changed

    property int id

    add.onClicked: addRoutine(routine)
    back.onClicked: closeOut()

    ExerciseListModel {
        id: elm
    }

    function reload(id, routine) {
        impl.id = id

        impl.routine = routine

        routineName.text = routine.name
        routineNotes.text = routine.notes
        elm.setExercises(routine.exercises)
    }

    exercises.delegate: ExerciseImpl {
        id: exercise
        height: 85 + 60 * listView.count
        clip: true

        onDeleteMe: {
            elm.removeRow(exID)
            routine.exercises = elm.exercises()
            impl.changed(routine)
        }

        onChanged: {
            model.sets = esm.sets()
            routine.exercises = elm.exercises()
            impl.changed()
        }

        function reloadData() {
            setData(model.sets)
            routine.exercises = elm.exercises()
            impl.changed()
        }

        Component.onCompleted: {
            reloadData()
        }
    }

    routineName.text: routine.name
    routineNotes.text: routine.notes

    routineName.onEditingFinished: {
        routine.name = routineName.text
        changed()
    }
    routineNotes.onEditingFinished: {
        routine.notes = routineNotes.text
        changed()
    }

    exercises.model: elm

    addExercise.onClicked: elm.add("")
}
