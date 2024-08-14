import QtQuick 2.15

ExerciseRoutineForm {
    id: impl
    mouse.onClicked: impl.clicked()

    routineName.text: routine.name
    routineNotes.text: routine.notes
}
