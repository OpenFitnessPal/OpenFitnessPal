import QtQuick

import OpenFitnessPal

Rectangle {
    id: settings

    color: Constants.bg

    function back() {
        if (stack.depth > 1) {
            stack.pop()
            return true
        }

        return false
    }

    BetterStackView {
        id: stack
        initialItem: indexPage

        anchors {
            top: parent.top
            bottom: parent.bottom
            left: parent.left
            right: parent.right

            topMargin: 10 * Constants.scalar
        }

        ExerciseIndexPage {
            id: indexPage

            onExercises: stack.push(exercisesTab)
            onRoutines: stack.push(routines)
            onCardio: stack.push(cardioTab)
        }

        // TODO: TODO:
        // May want to add a view/edit mode for exercises.
        ExerciseTab {
            id: exercisesTab

            visible: false
        }

        RoutinesTab {
            id: routines
            visible: false

            onEditRoutine: routine => {
                               routineEdit.bindedRoutine = routine
                               stack.push(routineEdit)
                           }
        }

        CardioTab {
            id: cardioTab

            visible: false
        }

        RoutineEdit {
            id: routineEdit
            visible: false

            onLog: exercises => {
                       exercisesTab.add(exercises)

                       stack.pop()
                       stack.pop()
                       stack.push(exercisesTab)
                   }
        }
    }
}
