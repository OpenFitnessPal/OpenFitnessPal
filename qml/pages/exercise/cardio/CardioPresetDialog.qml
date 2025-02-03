import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

AnimatedDialog {
    signal add(string name)

    property string selected

    id: presetDialog

    title: "Add Cardio Exercise"

    standardButtons: Dialog.Ok | Dialog.Cancel

    width: 300 * Constants.scalar

    ColumnLayout {
        anchors.fill: parent
        Repeater {
            id: rep
            model: ["Custom", "Walk", "Run", "Game", "Practice"]

            RadioButton {
                implicitHeight: 30 * Constants.scalar
                text: modelData

                onCheckedChanged: if (checked)
                                      presetDialog.selected = modelData

                font.pixelSize: 18 * Constants.scalar

                Component.onCompleted: if (index === 1)
                                           checked = true
            }
        }
    }

    onAccepted: add(selected)
}
