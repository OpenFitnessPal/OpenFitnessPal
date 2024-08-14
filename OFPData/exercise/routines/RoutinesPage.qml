import QtQuick 2.15

import OFPNative

RoutinesPageForm {
    ExerciseRoutinesModel {
        id: erm // what the sigma
    }

    function save() {
        erm.saveData()
    }

    function setRoutine(id, routine) {
        erm.setRowData(id, routine)
        routines.itemAtIndex(id).routine = routine
    }

    routines.model: erm
    routines.delegate: ExerciseRoutine {
        width: routines.width

        onClicked: {
            editRoutine(rtID, model.routine)
        }
    }

    add.onClicked: erm.add()

    back.onClicked: closeOut()

    Component.onCompleted: erm.loadData()
}
