import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OFPItems

RoundButton {
    id: btn

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
}
