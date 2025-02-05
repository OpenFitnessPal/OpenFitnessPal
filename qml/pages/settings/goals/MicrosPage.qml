import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

BaseSettingsTab {
    id: micros

    title: "Additional Goals"

    color: Constants.bg

    ColumnLayout {
        uniformCellSizes: true
        spacing: 0

        anchors {
            top: nav.bottom
            right: parent.right
            left: parent.left

            topMargin: 25 * Constants.scalar
        }

        Repeater {
            model: microsModel

            GoalField {
                required property var model

                Layout.fillWidth: true
                label: model.name
                key: model.data
                defaultValue: model.defaultValue

                suffix: model.suffix
            }
        }
    }
}
