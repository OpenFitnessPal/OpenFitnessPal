import QtQuick
import QtQuick.Shapes
import QtQuick.Controls
import QtQuick.Layouts
import QtCharts

import OpenFitnessPal

Item {
    property nutrientUnion nutrients

    property int daysBack: 1

    property double carbs: Math.round(nutrients.carbs)
    property double fat: Math.round(nutrients.fat)
    property double protein: Math.round(nutrients.protein)

    property double carbCalories: carbs * 4.0
    property double fatCalories: fat * 9.0
    property double proteinCalories: protein * 4.0

    property double calories: carbCalories + fatCalories + proteinCalories

    // Carbs, fat, protein values
    property list<double> values: [carbs, fat, protein]

    property list<double> percents: [carbCalories / calories, fatCalories
        / calories, proteinCalories / calories]

    // labels for the macro display
    property list<string> labels: ["Carbs", "Fat", "Protein"]
    property list<color> colors: ["lightblue", "#9500ff", "yellow"]

    ScrollView {
        id: scroll

        width: parent.width
        height: parent.height

        contentWidth: parent.width - effectiveScrollBarWidth

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 8 * Constants.scalar

            ChartView {
                id: chart

                backgroundColor: Constants.bg
                legend.visible: false
                backgroundRoundness: 0
                antialiasing: true

                margins {
                    bottom: 0
                    top: 0
                    left: 0
                    right: 0
                }

                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignHCenter

                implicitHeight: Math.min(scroll.width, scroll.height / 2)
                implicitWidth: height

                PieSeries {
                    id: pie

                    PieSlice {
                        label: labels[0]
                        value: isNaN(calories) ? 0 : values[0]
                        color: colors[0]
                    }

                    PieSlice {
                        label: labels[1]
                        value: isNaN(calories) ? 0 : values[1]
                        color: colors[1]
                    }

                    PieSlice {
                        label: labels[2]
                        value: isNaN(calories) ? 0 : values[2]
                        color: colors[2]
                    }

                    PieSlice {
                        value: isNaN(calories) ? 1 : 0
                        color: "gray"
                    }
                }
            }

            MacroHeader {}

            Repeater {
                model: macrosModel

                MacroDisplay {
                    value: values[index]
                    percent: percents[index] * 100.0
                }
            }

            // TODO: show calories

            // TODO: IF daysback > 1, show a bar chart
        }
    }
}
