import QtQuick
import QtQuick.Shapes
import QtQuick.Controls
import QtQuick.Layouts
import QtCharts

import OpenFitnessPal

RowLayout {
    required property var model
    required property int index

    required property string key

    required property int value
    required property int percent

    property int realValue: {
        if (isNaN(value))
            return 0

        return Math.round(value)
    }

    Layout.fillWidth: true

    uniformCellSizes: true

    Text {
        text: model.name
        color: colors[index]

        Layout.fillWidth: true
        font.pixelSize: 16 * Constants.scalar
    }

    Item {
        Layout.fillWidth: true
    }

    Item {
        Layout.fillWidth: true
    }

    Text {
        Layout.fillWidth: true
        horizontalAlignment: Text.AlignHCenter

        id: total
        text: realValue + "g"

        color: "gray"

        font.pixelSize: 14 * Constants.scalar
    }

    Text {
        Layout.fillWidth: true
        horizontalAlignment: Text.AlignHCenter

        id: percentText
        text: {
            let data = percent
            if (isNaN(data))
                data = 0

            return Math.round(data) + "%"
        }
        color: "gray"

        font.pixelSize: 14 * Constants.scalar
    }

    Text {
        id: goal
        Layout.fillWidth: true
        horizontalAlignment: Text.AlignHCenter

        text: goalManager[key.toLowerCase()] + "%"

        color: Constants.accent

        font.pixelSize: 14 * Constants.scalar
    }
}
