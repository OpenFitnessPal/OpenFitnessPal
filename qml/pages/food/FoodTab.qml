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

    property alias exerciseCalories: preview.exerciseCalories

    function add(mealNumber, serving) {
        listView.itemAtIndex(mealNumber - 1).addFood(serving)
    }

    NutritionPreview {
        id: preview

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
        }
    }
}
