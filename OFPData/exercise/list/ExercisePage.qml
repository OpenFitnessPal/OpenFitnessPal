import QtQuick 2.15
import QtQuick.Controls 2.15

import OFPNative

ExercisePageForm {
    id: exercisePageImpl

    property alias exercises: exercises

    ExerciseListModel {
        id: exercises
    }

    function addRoutine(routine) {
        exercises.addMultiple(routine.exercises)
        exercises.saveData(currentDate)
    }

    function reloadData() {
        exercises.clear()

        exercises.loadData(currentDate)
    }

    listView.delegate: ExerciseImpl {
        id: exercise
        height: 85 + 60 * listView.count
        clip: true

        onDeleteMe: {
            exercises.removeRow(exID)
            exercises.saveData(currentDate)
        }

        onChanged: {
            model.sets = esm.sets()
            exercises.saveData(currentDate)
        }

        function reloadData() {
            setData(model.sets)
        }

        Component.onCompleted: {
            reloadData()
        }
    }

    listView.model: exercises

    add.onClicked: exercises.add("")

    routines.onClicked: routinesRequested()
}
