import QtQuick
import QtQuick.Shapes
import QtQuick.Controls
import QtQuick.Layouts
import QtCharts

import OpenFitnessPal

RowLayout {
    required property double calories

    property double calorieGoal: parseInt(goal.text)

    Layout.fillWidth: true

    uniformCellSizes: true

    implicitHeight: 100 * Constants.scalar

    Text {
        text: "Calories"
        color: Constants.text

        Layout.fillWidth: true
        font.pixelSize: 18 * Constants.scalar
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

        text: isNaN(calories) ? 0 : calories

        color: "gray"

        font.pixelSize: 14 * Constants.scalar
    }

    Text {
        Layout.fillWidth: true
        horizontalAlignment: Text.AlignHCenter

        id: percent

        text: isNaN(calories) ? "0%" : Math.round(calories / parseInt(
                                                      goal.text) * 100.0) + "%"

        color: "gray"

        font.pixelSize: 14 * Constants.scalar
    }

    Text {
        id: goal
        Layout.fillWidth: true
        horizontalAlignment: Text.AlignHCenter

        text: goalManager.get("calories", 3000) + "cal"

        Component.onCompleted: goalManager.goalChanged.connect((key, data) => {
                                                                   if (key === "calories") {
                                                                       text = data + "cal"
                                                                   }
                                                               })
        color: Constants.accent

        font.pixelSize: 14 * Constants.scalar
    }
}
