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

    HMSField {
        id: field

        labeled: true
        useSeconds: false

        Component.onCompleted: setTime = model.value
        onTimeChanged: if (model.value !== time)
                           model.value = time

        Connections {
            target: model

            function onValueChanged() {
                field.setTime = model.value
            }
        }

        anchors {
            left: parent.horizontalCenter
            verticalCenter: parent.verticalCenter
        }
    }
}
