import QtQuick 2.15

import OpenFitnessPalContent

RoutinesPageForm {
    ExerciseRoutinesModel {
        id: erm // what the sigma
    }

    function save() {
        erm.saveData()
    }

    function setRoutine(id, routine) {
        erm.setRowData(id, routine)
    }

    routines.model: erm
    routines.delegate: ExerciseRoutineImpl {
        clip: true
        width: routines.width

        onClicked: {
            editRoutine(rtID, model.routine)
        }

        onDeleteRoutine: {
            erm.removeRow(rtID)
            erm.saveData()
        }
    }

    add.onClicked: erm.add()

    back.onClicked: closeOut()

    Component.onCompleted: erm.loadData()
}
