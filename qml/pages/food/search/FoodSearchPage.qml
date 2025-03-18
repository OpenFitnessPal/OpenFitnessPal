import QtQuick
import QtQuick.Controls

import OpenFitnessPal

ListView {
    signal add(var serving)

    id: listView

    function search(text) {
        fm.search(text)
        busy.running = true
    }

    property bool offlineSearch: false

    OMessageDialog {
        id: msg

        title: "Search Failed"
        text: ""
    }

    FoodModel {
        id: fm

        meal: 0
        date: new Date()

        offlineSearch: listView.offlineSearch
        settings: searchSettings

        onSearchComplete: busy.running = false
        onSearchFailed: message => {
                            msg.text = message
                            msg.open()
                            busy.running = false
                        }
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

    BusyIndicator {
        id: busy

        anchors.centerIn: parent
        running: false

        width: 50 * Constants.scalar
        height: 50 * Constants.scalar
    }
}
