import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

Rectangle {
    id: lnf

    required property string label
    required property string suffix

    required property var bindTarget
    required property string bindedProperty

    property alias value: number.text

    color: Constants.sub

    implicitHeight: 45 * Constants.scalar

    RowLayout {
        anchors {
            fill: parent

            bottomMargin: 1

            rightMargin: 10 * Constants.scalar
        }

        Text {
            Layout.fillWidth: true
            Layout.leftMargin: 15 * Constants.scalar

            color: Constants.text

            text: lnf.label

            font.pixelSize: 16 * Constants.scalar
        }

        SmallNumberField {
            id: number
            label: lnf.suffix

            bindTarget: lnf.bindTarget
            bindedProperty: lnf.bindedProperty

            background: Item {}

            font.pixelSize: 16 * Constants.scalar
        }
    }

    Rectangle {
        id: bottomLine

        anchors {
            left: parent.left
            right: parent.right

            bottom: parent.bottom
        }

        height: 1

        color: "gray"
    }
}
