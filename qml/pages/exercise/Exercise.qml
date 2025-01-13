import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

ColumnLayout {
    required property var model
    required property var sets

    spacing: 25 * Constants.scalar

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

    ListView {
        Layout.fillWidth: true
        Layout.preferredHeight: 75 * Constants.scalar * setsView.count - 25 * Constants.scalar

        Layout.leftMargin: 25 * Constants.scalar

        id: setsView

        interactive: false

        spacing: 25 * Constants.scalar

        model: sets

        delegate: ExerciseSet {
            width: setsView.width
        }
    }
}
