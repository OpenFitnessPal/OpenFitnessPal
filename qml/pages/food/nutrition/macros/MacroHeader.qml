import QtQuick
import QtQuick.Shapes
import QtQuick.Controls
import QtQuick.Layouts
import QtCharts

import OpenFitnessPal

RowLayout {
    property bool useAverage: false

    Layout.fillWidth: true

    uniformCellSizes: true

    Repeater {
        model: 3
        Item {
            Layout.fillWidth: true
        }
    }

    Repeater {
        model: useAverage ? ["Average", "Percent", "Goal"] : ["Total", "Percent", "Goal"]

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
