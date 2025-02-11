import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

RowLayout {
    id: header

    uniformCellSizes: true

    implicitHeight: 40 * Constants.scalar

    Repeater {
        model: 3

        Item {
            Layout.fillWidth: true
        }
    }

    Repeater {
        model: ["Total", "Goal", "Left"]

        Text {
            text: modelData
            color: Constants.text

            font.pixelSize: 14 * Constants.scalar

            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignBottom
        }
    }
}
