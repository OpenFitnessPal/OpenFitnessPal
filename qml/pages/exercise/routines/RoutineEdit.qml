import QtQuick
import QtQuick.Controls

import OpenFitnessPal

BaseSettingsTab {
    signal log(var exercises)

    id: routineEdit

    title: "Edit Routine"

    property var bindedRoutine: ({
                                     "name": "",
                                     "notes": ""
                                 })

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

    UnlabeledTextField {
        id: name

        bindTarget: bindedRoutine
        bindedProperty: "name"

        font.pixelSize: 22 * Constants.scalar
        font.bold: true

        background: Item {}

        anchors {
            top: nav.bottom
            left: parent.left
            right: parent.right

            topMargin: 10 * Constants.scalar
        }
    }

    UnlabeledTextField {
        id: notes

        bindTarget: bindedRoutine
        bindedProperty: "notes"

        font.pixelSize: 16 * Constants.scalar
        color: "gray"

        background: Item {}

        anchors {
            top: name.bottom
            left: parent.left
            right: parent.right

            leftMargin: 20 * Constants.scalar

            topMargin: 10 * Constants.scalar
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
