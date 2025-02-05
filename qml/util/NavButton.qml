import QtQuick
import QtQuick.Controls.Universal

import QtQuick.Layouts

import OpenFitnessPal

RoundButton {
    id: btn

    hoverEnabled: true

    property bool mousedOver: highlighted || hovered || down

    required property string label

    icon {
        source: "qrc:/" + label
        width: 24 * Constants.scalar
        height: 24 * Constants.scalar
    }

    contentItem: Image {
        source: btn.icon.source
        width: btn.icon.width
        height: btn.icon.height
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
    }

    background: Rectangle {
        implicitWidth: 32
        implicitHeight: 32

        radius: btn.radius
        visible: !btn.flat || btn.down || btn.checked || btn.highlighted
        color: (btn.highlighted || btn.hovered
                || btn.down) ? Constants.buttonHighlighted : Constants.button
    }
}
