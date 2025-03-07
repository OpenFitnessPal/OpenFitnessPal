import QtQuick
import QtQuick.Controls
import QtQuick.Layouts 6.6

import OpenFitnessPal

Rectangle {
    signal edit(var recipe)

    color: Constants.bg
    id: recipeTab

    RecipeView {
        id: listView

        recipes: recipeEditModel

        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            bottom: button.top
        }
    }

    Button {
        id: button
        font.pixelSize: 25 * Constants.scalar

        anchors {
            left: parent.left
            right: parent.right

            bottom: parent.bottom

            margins: 8 * Constants.scalar
        }

        text: "Add Recipe"
        onClicked: rm.add("New Recipe")

        background: Rectangle {
            color: button.pressed ? Constants.accentPressed : Constants.accent
            radius: 5 * Constants.scalar
        }
    }
}
