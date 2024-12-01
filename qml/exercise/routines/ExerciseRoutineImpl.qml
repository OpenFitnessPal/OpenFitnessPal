import QtQuick 2.15

ExerciseRoutineForm {
    mouse.onClicked: clicked()

    routineName.text: name
    routineNotes.text: notes

    remove.onClicked: deleteRoutine(rtID)
}
