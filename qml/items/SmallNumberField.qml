import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

TextField {
    required property string label

    required property var bindTarget
    required property var bindedProperty

    property int from: 0
    property int to: 9999

    property bool attentive: true

    implicitWidth: 100 * Constants.scalar
    Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
    id: repEdit

    background: Rectangle {
        border {
            color: "gray"
            width: 1
        }

        color: Constants.sub
    }

    rightPadding: txt.width + 2
    color: attentive ? Constants.accent : Constants.text

    inputMethodHints: "ImhDigitsOnly"
    validator: IntValidator {
        bottom: from
        top: to
    }

    font.pixelSize: 18 * Constants.scalar

    onTextEdited: bindTarget[bindedProperty] = text

    text: bindTarget[bindedProperty]

    Text {
        id: txt
        text: label

        anchors {
            verticalCenter: parent.verticalCenter
            right: parent.right

            rightMargin: 5 * Constants.scalar
        }

        color: "gray"
    }
}
