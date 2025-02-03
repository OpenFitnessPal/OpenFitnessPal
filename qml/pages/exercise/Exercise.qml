import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

ColumnLayout {
    signal remove(int idx)

    required property var model
    required property var sets

    spacing: 10 * Constants.scalar

    RowLayout {
        id: name

        NavButton {
            label: "Delete"
            onClicked: remove(model.idx)
        }

        UnlabeledTextField {
            Layout.fillWidth: true
            font.pixelSize: 20 * Constants.scalar
            font.bold: true

            background: Item {}

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
        Layout.preferredHeight: 46 * Constants.scalar * setsView.count

        Layout.leftMargin: 25 * Constants.scalar

        id: setsView

        interactive: false

        spacing: 5 * Constants.scalar

        model: sets

        delegate: ExerciseSet {}
    }
}
