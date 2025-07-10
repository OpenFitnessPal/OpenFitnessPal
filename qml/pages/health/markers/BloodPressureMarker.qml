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

    BloodPressureField {
        id: field

        Component.onCompleted: field.value = model.value
        onValueChanged: model.value = value

        Connections {
            target: model

            function onValueChanged() {
                field.value = model.value
            }
        }

        anchors {
            left: parent.horizontalCenter
            verticalCenter: parent.verticalCenter
        }
    }
}
