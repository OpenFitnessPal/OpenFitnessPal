import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

Rectangle {
    id: marker

    color: Constants.bg

    implicitHeight: 60 * Constants.scalar

    MarkerLabel {
        id: name

        onDeleteRequested: healthMarkerModel.remove(model.idx)
    }

    TimeMSField {
        id: field

        labeled: true

        Component.onCompleted: time = new Date(Date.parse(model.value))
        onTimeChanged: model.value = time.toISOString()

        Connections {
            target: model

            function onValueChanged() {
                field.time = new Date(Date.parse(model.value))
            }
        }

        anchors {
            left: parent.horizontalCenter
            verticalCenter: parent.verticalCenter
        }
    }
}
