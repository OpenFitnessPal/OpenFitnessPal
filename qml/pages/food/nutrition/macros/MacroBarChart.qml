import QtQuick
import QtQuick.Shapes
import QtQuick.Controls
import QtQuick.Layouts
import QtCharts

import OpenFitnessPal

StackedBarSeries {
    property bool weekView: false
    property list<color> colors
    property list<nutrientUnion> weekList: nutritionManager.weekList

    property date currentDate: dateManager.date

    property list<string> days: ["Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"]

    function updateCats() {
        let newCats = []
        for (var i = bar.days.length - 1; i > -1; --i) {
            let newDay = currentDate.getDay() - i
            if (newDay < 0)
                newDay += 7
            newCats.push(days[newDay])
        }

        // cats :)
        xAxis.categories = newCats
    }

    onCurrentDateChanged: updateCats()
    Component.onCompleted: updateCats()

    onWeekListChanged: () => {
                           let carbsList = []
                           let fatList = []
                           let proteinList = []

                           for (var i = 0; i < weekList.length; ++i) {
                               let n = weekList[i]

                               carbsList.push(n.carbs * 4.0)
                               fatList.push(n.fat * 9.0)
                               proteinList.push(n.protein * 4.0)
                           }

                           carbsBar.values = carbsList
                           fatBar.values = fatList
                           proteinBar.values = proteinList
                       }

    visible: weekView

    id: bar

    axisX: BarCategoryAxis {
        id: xAxis

        color: Constants.text
        labelsColor: Constants.text

        visible: weekView
    }

    axisY: ValueAxis {
        min: 0
        max: goalManager.calories

        color: Constants.text
        labelsColor: Constants.text
        gridLineColor: "transparent"

        visible: weekView
    }

    BarSet {
        id: carbsBar
        color: colors[0]
    }

    BarSet {
        id: fatBar
        color: colors[1]
    }

    BarSet {
        id: proteinBar
        color: colors[2]
    }
}
