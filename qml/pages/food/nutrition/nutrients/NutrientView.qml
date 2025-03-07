import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

ColumnLayout {
    uniformCellSizes: true
    property bool isMacro: ["carbs", "fat", "protein"].includes(model.data)

    property bool weekView
    property nutrientUnion nutrients: weekView ? nutritionManager.week : nutritionManager.today

    RowLayout {
        uniformCellSizes: true

        Text {
            text: model.name
            color: Constants.text

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
            text: {
                let data = nutrients[model.data]
                if (isNaN(data))
                    data = 0

                return Math.round(data)
            }

            color: "gray"

            font.pixelSize: 14 * Constants.scalar
        }

        Text {
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter

            id: goal
            text: isMacro ? goalManager[model.data + "Grams"] : goalManager.get(
                                model.data, model.defaultValue)
            color: "gray"

            Component.onCompleted: goalManager.goalChanged.connect(
                                       (key, data) => {
                                           if (isMacro) {
                                               return
                                           }

                                           if (key === model.data) {
                                               text = data
                                           }
                                       })

            font.pixelSize: 14 * Constants.scalar
        }

        Text {
            id: remaining
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter

            text: parseInt(goal.text - total.text) + model.suffix
            color: "gray"

            font.pixelSize: 14 * Constants.scalar
        }
    }

    ProgressBar {
        Layout.fillWidth: true
        from: 0
        to: goal.text === "0" ? 1 : parseInt(goal.text)

        value: to - parseInt(remaining.text)
    }
}
