import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Shapes
import QtCharts

import OpenFitnessPal

BaseTab {
    id: progressTab

    title: "Health Progress"

    // list of list of health markers
    property var currentList: [[]]
    property string choice: "Resting HR"

    property alias daysBack: select.daysBack

    onDaysBackChanged: currentList = pm.load(daysBack)

    function resetFlatList() {
        let newList = []

        for (var i = 0; i < currentList.length; ++i) {
            let curList = currentList[i]

            for (var j = 0; j < curList.length; ++j) {
                let marker = curList[j]

                if (marker.name === choice) {
                    newList.push(marker)
                    break
                }
            }
        }

        line.flatList = newList
    }

    onCurrentListChanged: resetFlatList()
    onChoiceChanged: resetFlatList()

    HealthMarkerProgressManager {
        id: pm

        date: dateManager.date
        onDateChanged: currentList = pm.load(daysBack)
        Component.onCompleted: currentList = pm.load(daysBack)
    }

    HealthDaysBackDialog {
        id: backDialog

        onSelect: (selection, label) => {
                      select.text = label
                      select.daysBack = selection
                  }
    }

    MarkerChoiceDialog {
        id: choiceDialog

        raw: true

        onChoice: choice => progressTab.choice = choice
    }

    DaysBackButton {
        id: select

        text: "Past Week"
        daysBack: 7

        anchors {
            top: nav.bottom
            left: parent.left
            right: parent.right

            topMargin: 5 * Constants.scalar
        }
    }

    TextButton {
        id: choiceButton

        name: choice
        fontSize: 18

        implicitHeight: 45 * Constants.scalar

        anchors {
            top: select.bottom
            left: parent.left
            right: parent.right

            topMargin: 15 * Constants.scalar
        }

        onClicked: choiceDialog.open()
    }

    ChartView {
        id: chart

        anchors {
            top: choiceButton.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom

            margins: 10 * Constants.scalar
        }

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

        // Layout.fillWidth: true
        // Layout.fillHeight: true
        // Layout.alignment: Qt.AlignHCenter
        LineSeries {
            width: 6 * Constants.scalar
            color: Constants.accent
            capStyle: "RoundCap"

            property list<healthMarker> flatList
            property list<double> yValues

            onFlatListChanged: {
                if (flatList.length === 0)
                    return

                yValues = []
                let categories = []
                removePoints(0, count)

                for (var i = 0; i < flatList.length; ++i) {
                    let marker = flatList[i]
                    let value = marker.value
                    let name = marker.name

                    // Format differently based on the individual marker
                    // TODO: Make the Y axis do this as well
                    switch (name) {
                    case "Mile Time":
                    {
                        value /= 60
                        break
                    }
                    case "Blood Pressure":
                    {
                        let split = value.split("/")
                        let sys = split[0]
                        let dia = split[1]

                        // TODO: Create a separate line series for systolic and diastolic
                        // yValues.push(dia)
                        value = sys

                        break
                    }
                    case "Sleep":
                    {
                        value /= 3600
                        break
                    }
                    default:
                        break
                    }

                    yValues.push(value)

                    append(i, value)
                    categories.push(i)
                }

                // prepend and append to make the graph complete
                insert(0, -1, yValues[0])
                append(flatList.length + 1, at(count - 1).y)

                xAxis.categories = categories
            }

            id: line

            axisX: BarCategoryAxis {
                id: xAxis

                color: Constants.text
                labelsColor: "transparent"
                gridLineColor: "transparent"
            }

            axisY: ValueAxis {
                min: {
                    if (line.yValues.length === 0) {
                        return 0
                    }

                    let m = Math.min(...line.yValues)
                    return m - m / 10
                }

                max: {
                    if (line.yValues.length === 0) {
                        return 1
                    }

                    let m = Math.max(...line.yValues)
                    return m + m / 10
                }

                color: Constants.text
                labelsColor: Constants.text
                // gridLineColor: "transparent"
            }
        }
    }
}
