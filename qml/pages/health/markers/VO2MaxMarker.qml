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

    SmallNumberField {
        label: ""

        bindTarget: model
        bindedProperty: "value"

        attentive: false

        anchors {
            left: parent.horizontalCenter
            right: parent.right

            verticalCenter: parent.verticalCenter

            rightMargin: 10 * Constants.scalar
        }
    }
}
