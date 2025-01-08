import QtQuick
import QtQuick.Controls

import OpenFitnessPal

Button {
    id: control
    
    required property string label
    
    background: Rectangle {
        color: control.pressed ? Constants.buttonHighlighted : Constants.button
        radius: 3
    }
    
    contentItem: Image {
        source: "qrc:/" + label
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
