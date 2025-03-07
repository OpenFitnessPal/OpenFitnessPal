import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

Rectangle {
    signal clicked

    id: nutritionPreview

    color: Constants.button

    implicitHeight: 90 * Constants.scalar

    property double foodCalories: nutritionManager.today.calories
    // TODO: also extract this
    // will need for overview page
    property double exerciseCalories
    property double calorieGoal: goalManager.calories

    property double remaining: calorieGoal - (isNaN(
                                                  foodCalories) ? 0 : foodCalories)
                               + exerciseCalories

    readonly property list<string> labels: ["Goal", "", "Food", "", "Exercise", ""]

    MouseArea {
        anchors.fill: parent
        onClicked: parent.clicked()
    }

    Text {
        id: label
        text: "Calories Remaining"

        color: Constants.text

        anchors {
            top: parent.top
            left: parent.left

            topMargin: 8 * Constants.scalar
            leftMargin: 20 * Constants.scalar
        }

        font.pixelSize: 16 * Constants.scalar
    }

    RowLayout {
        id: layout
        uniformCellSizes: true

        anchors {
            left: label.left
            right: parent.right
            top: label.bottom
            bottom: parent.bottom

            leftMargin: 5 * Constants.scalar
            rightMargin: 15 * Constants.scalar

            bottomMargin: 10 * Constants.scalar
        }

        Repeater {
            model: [calorieGoal, "-", isNaN(
                    foodCalories) ? 0 : foodCalories, "+", exerciseCalories, "="]

            ColumnLayout {
                Layout.fillHeight: true

                Text {
                    Layout.fillWidth: true
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter

                    text: typeof modelData === "number" ? Math.round(
                                                              modelData) : modelData

                    font.pixelSize: (["-", "+", "="].includes(
                                         modelData) ? 24 : 16) * Constants.scalar
                    color: Constants.text
                }

                Text {
                    Layout.fillWidth: true
                    verticalAlignment: Text.AlignTop
                    horizontalAlignment: Text.AlignHCenter

                    text: labels[index]

                    font.pixelSize: 14 * Constants.scalar

                    color: "gray"
                }
            }
        }

        ColumnLayout {
            Layout.fillHeight: true

            Text {
                Layout.fillWidth: true
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter

                text: Math.round(remaining)

                font.pixelSize: 18 * Constants.scalar
                font.bold: true

                color: Constants.text
            }

            Text {
                Layout.fillWidth: true
                verticalAlignment: Text.AlignTop
                horizontalAlignment: Text.AlignHCenter

                text: "Remaining"

                font.pixelSize: 14 * Constants.scalar

                color: "gray"
            }
        }
    }
}
