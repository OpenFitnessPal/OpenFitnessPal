import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

BaseTab {
    id: markersTab

    title: "Health Markers"

    ListView {
        id: listView
        anchors {
            top: nav.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom

            topMargin: 10 * Constants.scalar
        }

        Component.onCompleted: hm.load()

        model: HealthMarkerModel {
            id: hm

            date: dateManager.date
        }

        delegate: Text {
            width: listView.width
            color: Constants.text

            font.pixelSize: 30

            height: 80 * Constants.scalar
            text: model.name

            Component.onCompleted: console.log(name, value, height, width)
        }
    }
}
