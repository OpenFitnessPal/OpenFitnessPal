import QtQuick
import QtQuick.Controls
import QtQuick.Shapes
import QtQuick.Layouts

import OpenFitnessPal

BaseSettingsTab {
    id: foodEdit

    property var serving: {
        "name": "",
        "units": 0,
        "size": {}
    }

    property double carbs: Math.round(
                               serving.size.multiplier(
                                   serving.units) * serving.item.nutrients.carbs * 10.) / 10.
    property double fat: Math.round(
                             serving.size.multiplier(
                                 serving.units) * serving.item.nutrients.fat * 10.) / 10.
    property double protein: Math.round(
                                 serving.size.multiplier(
                                     serving.units) * serving.item.nutrients.protein * 10.) / 10.

    property double carbCalories: carbs * 4.0
    property double fatCalories: fat * 9.0
    property double proteinCalories: protein * 4.0

    property double calories: carbCalories + fatCalories + proteinCalories

    /** Data for Macro Display */

    // Carbs, fat, protein values
    property list<double> values: [carbs, fat, protein]

    // Carbs, fat, protein as percentages of the total calorie makeup
    property list<double> percents: [//.
        Math.round(carbCalories / calories * 100.0), //.
        Math.round(fatCalories / calories * 100.0), //.
        Math.round(proteinCalories / calories * 100.0) //.
    ]

    // labels for the macro display
    property list<string> labels: ["Carbs", "Fat", "Protein"]
    property list<color> colors: ["lightblue", "#9500ff", "yellow"]

    ServingSizeModel {
        id: fsm
    }

    onServingChanged: {
        fsm.clear()
        if (serving.name !== "") {
            fsm.add(serving.item.servingSizes)
        }
    }

    title: "Edit Serving"

    ServingSizeDialog {
        id: servingDialog
        model: fsm

        onSelect: selection => {
                      serving.size = selection
                  }
    }

    ColumnLayout {
        spacing: 0
        anchors {
            top: nav.bottom
            left: parent.left
            right: parent.right

            topMargin: 10 * Constants.scalar
        }

        UnlabeledTextField {
            id: name

            bindTarget: serving
            bindedProperty: "name"

            font.pixelSize: 22 * Constants.scalar
            font.bold: true

            background: Item {}

            Layout.fillWidth: true
        }

        LabeledNumberField {
            Layout.fillWidth: true

            label: "Servings"
            suffix: ""

            bindTarget: serving
            bindedProperty: "units"
        }

        Rectangle {
            signal clicked

            Layout.fillWidth: true

            id: combo

            color: Constants.sub

            implicitHeight: 45 * Constants.scalar

            MouseArea {
                anchors.fill: parent
                onClicked: servingDialog.open()

                RowLayout {
                    anchors {
                        fill: parent

                        rightMargin: 10 * Constants.scalar
                    }

                    Text {
                        Layout.fillWidth: true
                        Layout.leftMargin: 15 * Constants.scalar

                        color: Constants.text

                        text: "Serving Size"

                        font.pixelSize: 16 * Constants.scalar
                    }

                    Text {
                        color: Constants.accent

                        text: serving.size.unit(1)

                        font.pixelSize: 16 * Constants.scalar
                    }
                }
            }
        }

        RowLayout {
            uniformCellSizes: true
            Layout.fillWidth: true

            Layout.margins: 10 * Constants.scalar

            Layout.preferredHeight: 90 * Constants.scalar

            Item {
                Layout.fillHeight: true
                Layout.preferredWidth: 90 * Constants.scalar

                Shape {
                    id: shape
                    anchors.centerIn: parent
                    width: Math.min(parent.width, parent.height) * 0.8
                    height: width

                    property double stroke: 10 * Constants.scalar

                    ShapePath {
                        id: carbPath

                        strokeColor: colors[0]
                        strokeWidth: shape.stroke
                        fillColor: "transparent"

                        startX: shape.width / 2
                        startY: 0

                        PathAngleArc {
                            id: carbArc

                            centerX: shape.width / 2
                            centerY: centerX

                            radiusX: centerX
                            radiusY: centerX

                            startAngle: -90
                            sweepAngle: carbCalories / calories * 360.0
                        }
                    }

                    ShapePath {
                        id: fatPath

                        strokeColor: colors[1]
                        strokeWidth: shape.stroke
                        fillColor: "transparent"

                        startX: shape.width / 2
                        startY: 0

                        PathAngleArc {
                            id: fatArc

                            centerX: shape.width / 2
                            centerY: centerX

                            radiusX: centerX
                            radiusY: centerX

                            startAngle: carbArc.startAngle + carbArc.sweepAngle
                            sweepAngle: fatCalories / calories * 360.0
                        }
                    }

                    ShapePath {
                        id: proteinPath

                        strokeColor: colors[2]
                        strokeWidth: shape.stroke
                        fillColor: "transparent"

                        startX: shape.width / 2
                        startY: 0

                        PathAngleArc {
                            centerX: shape.width / 2
                            centerY: centerX

                            radiusX: centerX
                            radiusY: centerX

                            startAngle: fatArc.startAngle + fatArc.sweepAngle
                            sweepAngle: proteinCalories / calories * 360.0
                        }
                    }
                }

                Text {
                    anchors.centerIn: parent
                    text: Math.round(calories)
                    color: Constants.text

                    width: 60 * Constants.scalar

                    fontSizeMode: Text.Fit

                    font {
                        bold: true
                        pixelSize: 20 * Constants.scalar
                    }

                    horizontalAlignment: Text.AlignHCenter
                }
            }

            Repeater {
                model: 3

                ColumnLayout {
                    Layout.fillHeight: true
                    // Layout.fillWidth: true
                    Layout.alignment: Qt.AlignCenter

                    Text {
                        Layout.fillWidth: true

                        color: colors[index]
                        text: (isNaN(
                                   percents[index]) ? 0 : percents[index]) + "%"

                        font.pixelSize: 14 * Constants.scalar
                        horizontalAlignment: Text.AlignHCenter
                    }

                    Text {
                        Layout.fillWidth: true

                        color: Constants.text
                        text: (isNaN(values[index]) ? 0 : values[index]) + "g"

                        font.pixelSize: 18 * Constants.scalar
                        horizontalAlignment: Text.AlignHCenter
                    }

                    Text {
                        Layout.fillWidth: true

                        color: Constants.text
                        text: labels[index]

                        font.pixelSize: 14 * Constants.scalar
                        horizontalAlignment: Text.AlignHCenter
                    }
                }
            }
        }
    }
}
