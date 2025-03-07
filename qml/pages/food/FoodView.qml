import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

ListView {
    id: listView
    required property var foods

    property bool editable: true

    model: foods

    signal foodRemoved
    signal edit(var serving)

    spacing: 5 * Constants.scalar

    Layout.fillHeight: true
    Layout.fillWidth: true

    height: (count * (65 * Constants.scalar + spacing))
    contentHeight: height

    interactive: false
    clip: false

    function fixHeight() {
        height = (count * (65 * Constants.scalar
                           + spacing)) // needs to be force-set for some reason
    }

    onHeightChanged: fixHeight()
    onCountChanged: fixHeight()

    delegate: FoodPreview {
        width: listView.width
        height: 65 * Constants.scalar
        onDeleteRequested: {
            listView.foods.remove(idx)
            foodRemoved()
        }

        canBeDeleted: listView.editable

        onClicked: edit(model)
    }
}
