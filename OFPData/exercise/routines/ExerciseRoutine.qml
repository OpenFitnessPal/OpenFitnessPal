import QtQuick 2.15

ExerciseRoutineForm {
    id: impl
    mouse.onClicked: impl.clicked()

    routineName.text: name
    routineNotes.text: notes

    remove.onClicked: deleteRoutine(rtID)
}
