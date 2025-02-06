import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

Rectangle {
    signal nutritionView

    signal search(int mealNumber)
    signal edit(var serving)

    id: foodTab

    color: Constants.bg

    property date currentDate: new Date()

    property nutrientUnion blankNutrients

    property list<double> mealCalories
    property double calories: {
        let sum = 0
        for (var i = 0; i < mealCalories.length; ++i) {
            sum += mealCalories[i]
        }

        return sum
    }

    property list<nutrientUnion> mealNutrients
    property nutrientUnion nutrients: {
        var sum
        for (var i = 0; i < mealNutrients.length; ++i) {
            if (i === 0) {
                sum = mealNutrients[i]
            } else {
                sum = sum.add(mealNutrients[i])
            }
        }

        if (typeof sum === "undefined") {
            sum = blankNutrients
        }

        return sum
    }

    property alias exerciseCalories: preview.exerciseCalories

    function add(mealNumber, serving) {
        listView.itemAtIndex(mealNumber - 1).addFood(serving)
    }

    NutritionPreview {
        id: preview

        foodCalories: parent.calories

        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }

        onClicked: nutritionView()
    }

    ListView {
        anchors {
            top: preview.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

        id: listView

        boundsBehavior: Flickable.StopAtBounds

        clip: true
        spacing: 10 * Constants.scalar

        model: mealNamesModel

        delegate: MealLog {
            width: listView.width

            required property var model

            mealNumber: model.idx + 1
            mealName: model.name

            onAdd: foodTab.search(mealNumber)
            onEdit: serving => foodTab.edit(serving)

            onCaloriesChanged: foodTab.mealCalories[model.idx] = calories
            onNutrientsChanged: foodTab.mealNutrients[model.idx] = nutrients

            currentDate: foodTab.currentDate
        }
    }
}
