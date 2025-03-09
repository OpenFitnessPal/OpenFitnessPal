import QtQuick
import QtQuick.Layouts

import OpenFitnessPal

RowLayout {
    signal deleteRequested

    anchors {
        verticalCenter: parent.verticalCenter
        left: parent.left

        leftMargin: 10 * Constants.scalar
    }

    NavButton {
        id: del
        label: "Delete"
        onClicked: deleteRequested()

        Layout.maximumWidth: 50 * Constants.scalar
    }

    Text {
        id: name

        color: Constants.text

        font.pixelSize: 20 * Constants.scalar

        text: model.name
    }
}
