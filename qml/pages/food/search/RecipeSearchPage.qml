import QtQuick
import QtQuick.Controls

import OpenFitnessPal

ListView {
    signal add(var serving)

    id: listView

    function search(text) {
        recipeSearchModel.search(text)
    }

    model: recipeSearchModel
    spacing: 5 * Constants.scalar

    boundsBehavior: Flickable.StopAtBounds
    interactive: true
    clip: true

    delegate: RecipePreview {
        width: listView.width

        canBeDeleted: false

        onClicked: listView.add(model.recipe.asFood(1))
    }
}
