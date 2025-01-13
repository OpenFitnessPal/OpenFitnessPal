import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

BaseSettingsTab {
    signal editRoutine(var routine)

    id: exercisePage

    title: "Routines"

    Component.onCompleted: erm.load()

    ExerciseRoutineModel {
        id: erm
    }

    ListView {
        id: listView

        clip: true

        anchors {
            top: nav.bottom
            bottom: button.top
            left: parent.left
            right: parent.right

            topMargin: 5 * Constants.scalar

            leftMargin: 10 * Constants.scalar
        }

        model: erm

        spacing: 20 * Constants.scalar

        boundsBehavior: Flickable.StopAtBounds

        delegate: RoutinePreview {
            width: listView.width

            onClicked: editRoutine(model)
            onDeleteRequested: erm.remove(model.idx)
        }
    }

    Button {
        id: button
        font.pixelSize: 25 * Constants.scalar

        anchors {
            left: parent.left
            right: parent.right

            bottom: parent.bottom

            margins: 8 * Constants.scalar
        }

        text: "Add Routine"
        onClicked: erm.add("New Routine")

        background: Rectangle {
            color: button.pressed ? Constants.accentPressed : Constants.accent
            radius: 5 * Constants.scalar
        }
    }
}
