import QtQuick
import QtQuick.Controls

import OpenFitnessPal

BaseSettingsTab {
    signal log(var exercises)

    id: routineEdit

    title: "Edit Routine"

    property var bindedRoutine

    NavButton {
        width: 40 * Constants.scalar
        height: 40 * Constants.scalar

        label: "Forward"
        onClicked: {
            log(bindedRoutine.exercises.data())
        }

        background: Item {}

        anchors {
            top: parent.top
            right: parent.right

            topMargin: 10
            rightMargin: 30 * Constants.scalar
        }
    }

    LabeledTextField {
        id: name

        bindTarget: bindedRoutine
        bindedProperty: "name"

        label: "Name"

        font.pixelSize: 20 * Constants.scalar

        anchors {
            top: nav.bottom
            left: parent.left
            right: parent.right

            topMargin: 10 * Constants.scalar
        }
    }

    LabeledTextField {
        id: notes

        label: "Notes"

        bindTarget: bindedRoutine
        bindedProperty: "notes"

        font.pixelSize: 16 * Constants.scalar

        anchors {
            top: name.bottom
            left: parent.left
            right: parent.right

            topMargin: 20 * Constants.scalar
        }
    }

    ExerciseList {
        model: bindedRoutine.exercises

        anchors {
            top: notes.bottom
            bottom: parent.bottom
            left: parent.left
            right: parent.right

            topMargin: 5 * Constants.scalar
        }
    }
}
