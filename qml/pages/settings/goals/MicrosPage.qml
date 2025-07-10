import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

BaseTab {
    id: micros

    title: "Additional Goals"

    color: Constants.bg

    ScrollView {
        id: scroll
        anchors {
            top: nav.bottom
            right: parent.right
            left: parent.left
            bottom: parent.bottom

            topMargin: 25 * Constants.scalar
        }

        ColumnLayout {
            uniformCellSizes: true
            spacing: 0

            width: parent.width - scroll.effectiveScrollBarWidth

            // height: parent.height
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
}
