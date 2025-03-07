import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

Button {
    required property string label
    required property int buttonWidth
    required property int buttonHeight

    Layout.maximumHeight: buttonHeight * Constants.scalar
    Layout.maximumWidth: buttonWidth * Constants.scalar
    
    id: image
    icon.source: "qrc:/" + label
    icon.width: (buttonWidth - 30) * Constants.scalar
    icon.height: (buttonHeight - 30) * Constants.scalar
    icon.color: Constants.accent
    
    background: Item {}
    
    Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
}
