import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

ListView {
    signal search(int mealNumber)
    signal edit(var serving)

    function add(mealNumber, serving) {
        console.log(mealNumber, serving)
        itemAtIndex(mealNumber - 1).addFood(serving)
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

        onAdd: listView.search(mealNumber)
        onEdit: serving => listView.edit(serving)
    }
}
