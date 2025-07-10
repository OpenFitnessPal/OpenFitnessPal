import QtQuick

import OpenFitnessPal

ListView {
    id: listView

    spacing: 20 * Constants.scalar
    clip: true

    boundsBehavior: Flickable.StopAtBounds

    move: Transition {
        NumberAnimation { properties: "y"; duration: 300; easing.type: Easing.OutQuad }
    }

    displaced: Transition {
        NumberAnimation { properties: "y"; duration: 300; easing.type: Easing.OutQuad }
    }

    anchors {
        top: nav.bottom
        bottom: parent.bottom
        left: parent.left
        right: parent.right

        margins: 10
    }

    model: mealNamesModel

    Component.onCompleted: model.load()

    delegate: MealNameView {
        width: listView.width
    }
}
