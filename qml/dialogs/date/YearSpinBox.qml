import QtQuick
import QtQuick.Layouts

import OpenFitnessPal

RowLayout {
    id: month
    property int value: bindTarget[bindedProperty]

    required property var bindTarget
    required property string bindedProperty

    onValueChanged: bindTarget[bindedProperty] = value

    NavButton {
        background: Item {}

        Layout.preferredWidth: 40 * Constants.scalar
        Layout.preferredHeight: 40 * Constants.scalar
        Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter

        label: "Back"
        onClicked: {
            if (value > 1970) {
                value--
            }
        }
    }

    Text {
        Layout.fillWidth: true
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        font.pixelSize: 20 * Constants.scalar
        color: Constants.text

        text: value
    }

    NavButton {
        background: Item {}

        Layout.preferredWidth: 40 * Constants.scalar
        Layout.preferredHeight: 40 * Constants.scalar
        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter

        label: "Forward"
        onClicked: {
            value++
        }
    }
}
