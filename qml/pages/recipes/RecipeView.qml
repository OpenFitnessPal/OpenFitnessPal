import QtQuick
import QtQuick.Controls
import QtQuick.Layouts 6.6

import OpenFitnessPal

ListView {
    property bool editable: true
    id: listView

    model: rm

    Component.onCompleted: rm.load()

    clip: true
    boundsBehavior: Flickable.StopAtBounds

    delegate: RecipePreview {
        width: listView.width
        clip: true

        canBeDeleted: listView.editable

        onDeleteRequested: rm.remove(model.idx)
        onEdit: recipe => recipeTab.edit(recipe)
    }
}
