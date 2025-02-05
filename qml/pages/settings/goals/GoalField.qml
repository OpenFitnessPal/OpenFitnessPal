import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

Rectangle {
    id: lnf

    required property string label
    required property string suffix

    required property string key
    required property int defaultValue

    property alias value: number.text

    property int from: 0
    property int to: 99999

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

            from: lnf.from
            to: lnf.to

            bindTarget: null
            bindedProperty: ""

            onTextChanged: goalManager.set(key, text)
            text: goalManager.get(key, defaultValue)

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
