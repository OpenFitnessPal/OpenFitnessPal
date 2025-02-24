import QtQuick
import QtQuick.Shapes
import QtQuick.Controls
import QtQuick.Layouts
import QtCharts

import OpenFitnessPal

StackedBarSeries {
    property int daysBack: 1
    property list<color> colors
    property list<nutrientUnion> dailyNutrients

    property int currentDayOfWeek: 0

    property list<string> days: ["Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"]

    onCurrentDayOfWeekChanged: {
        let newCats = []
        for (var i = days.length - 1; i > -1; --i) {
            let newDay = currentDayOfWeek - i
            if (newDay < 0)
                newDay += 7
            newCats.push(days[newDay])
        }

        // cats :)
        xAxis.categories = newCats
    }

    function updateNutrients() {
        let carbsList = []
        let fatList = []
        let proteinList = []

        for (var i = dailyNutrients.length - 1; i > -1; --i) {
            carbsList.push(dailyNutrients[i].carbs * 4.0)
            fatList.push(dailyNutrients[i].fat * 9.0)
            proteinList.push(dailyNutrients[i].protein * 4.0)
        }

        carbsBar.values = carbsList
        fatBar.values = fatList
        proteinBar.values = proteinList
    }

    visible: daysBack > 1

    id: bar

    axisX: BarCategoryAxis {
        id: xAxis

        color: Constants.text
        labelsColor: Constants.text

        visible: daysBack > 1
    }

    axisY: ValueAxis {
        min: 0
        max: calorieDisplay.calorieGoal

        color: Constants.text
        labelsColor: Constants.text
        gridLineColor: "transparent"

        visible: daysBack > 1
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
