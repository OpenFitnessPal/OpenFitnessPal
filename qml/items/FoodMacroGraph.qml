import QtQuick
import QtQuick.Controls
import QtQuick.Shapes
import QtQuick.Layouts

import OpenFitnessPal

RowLayout {
    required property list<double> values
    required property list<double> percents
    required property double calories

    property list<color> colors: ["lightblue", "#9500ff", "yellow"]
    property list<string> labels: ["Carbs", "Fat", "Protein"]

    id: graph
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

            property double stroke: 5 * Constants.scalar

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
                    sweepAngle: percents[0] * 3.6
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
                    sweepAngle: percents[1] * 3.6
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
                    sweepAngle: percents[2] * 3.6
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
            Layout.alignment: Qt.AlignCenter

            Text {
                Layout.fillWidth: true

                color: colors[index]
                text: (isNaN(percents[index]) ? 0 : percents[index]) + "%"

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
