import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

Rectangle {
    // TODO: stack view w/ cardio, exercise, routines
    signal routines

    id: exercisePage

    color: Constants.bg

    Component.onCompleted: em.load()

    ExerciseModel {
        id: em
    }

    RowLayout {
        id: buttons
        uniformCellSizes: true
        spacing: 20

        anchors {
            top: parent.top
            left: parent.left
            right: parent.right

            margins: 8 * Constants.scalar
        }

        Button {
            Layout.fillWidth: true
            font.pixelSize: 20 * Constants.scalar

            text: "Add Exercise"
            onClicked: em.add("Exercise")
        }

        // TODO: Should this be a separate option on the initial page?
        Button {
            Layout.fillWidth: true
            font.pixelSize: 20 * Constants.scalar

            text: "Routines"
            onClicked: routines()
        }
    }

    ListView {
        id: listView

        clip: true

        anchors {
            top: buttons.bottom
            bottom: parent.bottom
            left: parent.left
            right: parent.right

            topMargin: 25 * Constants.scalar
        }

        spacing: 20 * Constants.scalar
        topMargin: 15 * Constants.scalar

        boundsBehavior: Flickable.StopAtBounds

        model: em

        delegate: ColumnLayout {
            required property var model
            required property var sets

            spacing: 25 * Constants.scalar

            width: listView.width

            // TODO: own components
            RowLayout {
                id: name

                NavButton {
                    label: "Delete"
                    onClicked: em.remove(model.idx)
                }

                LabeledTextField {
                    Layout.fillWidth: true
                    font.pixelSize: 25 * Constants.scalar

                    label: "Exercise Name"

                    bindTarget: model
                    bindedProperty: "name"
                }

                NavButton {
                    label: "Add"
                    onClicked: sets.add()
                }
            }

            Rectangle {
                id: setRect
                color: Constants.sub
                Layout.fillWidth: true
                Layout.preferredHeight: 75 * Constants.scalar * setsView.count
                                        - 25 * Constants.scalar

                Layout.leftMargin: 25 * Constants.scalar

                ListView {
                    id: setsView
                    anchors.fill: parent
                    interactive: false

                    spacing: 25 * Constants.scalar

                    model: sets

                    delegate: RowLayout {
                        width: parent.width
                        implicitHeight: 60 * Constants.scalar

                        NavButton {
                            label: "Delete"
                            onClicked: sets.remove(idx)
                        }

                        LabeledSpinBox {
                            editable: true
                            label: "Reps"

                            bindTarget: model
                            bindedProperty: "reps"

                            Layout.fillWidth: true
                        }

                        LabeledSpinBox {
                            editable: true
                            label: "Weight"

                            bindTarget: model
                            bindedProperty: "weight"

                            Layout.fillWidth: true
                        }
                    }
                }
            }
        }
    }
}
