import QtQuick
import QtQuick.Controls

import OpenFitnessPal

ListView {
    signal add(var serving)

    id: listView

    function search(text) {
        fm.search(text)
    }

    property bool offlineSearch: false

    FoodModel {
        id: fm

        meal: 0
        date: new Date()

        offlineSearch: listView.offlineSearch
        settings: searchSettings
    }

    model: fm
    spacing: 5 * Constants.scalar

    boundsBehavior: Flickable.StopAtBounds
    interactive: true
    clip: true

    delegate: FoodPreview {
        width: listView.width
        height: 65 * Constants.scalar

        canBeDeleted: false
        onClicked: listView.add(model.serving)
    }
}
