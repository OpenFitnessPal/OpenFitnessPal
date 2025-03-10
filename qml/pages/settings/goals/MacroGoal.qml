import QtQuick
import QtQuick.Controls.Universal
import QtQuick.Layouts

import OpenFitnessPal

ColumnLayout {
    required property string label
    required property string key

    property alias value: slider.value

    property int calories: goalManager.calories

    property color handleColor: "red"

    function accept() {
        goalManager[key] = value
    }

    Text {
        text: label
        font.pixelSize: 16 * Constants.scalar
        color: Constants.text

        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    Text {
        id: gramPreview
        font.pixelSize: 16 * Constants.scalar
        color: Constants.text

        text: goalManager.getMacroGrams(value, label === "Fat" ? 9 : 4) + "g"

        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    Text {
        text: value + "%"

        font.pixelSize: 16 * Constants.scalar
        color: handleColor

        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    Slider {
        Layout.fillHeight: true
        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

        handle: Rectangle {
            implicitWidth: 30 * Constants.scalar
            implicitHeight: 30 * Constants.scalar

            x: slider.leftPadding + (slider.horizontal ? slider.visualPosition * (slider.availableWidth - width) : (slider.availableWidth - width) / 2)
            y: slider.topPadding
               + (slider.horizontal ? (slider.availableHeight - height) / 2 : slider.visualPosition
                                      * (slider.availableHeight - height))

            radius: 15 * Constants.scalar
            color: handleColor
        }

        id: slider

        orientation: "Vertical"

        from: 0
        to: 100

        Component.onCompleted: {
            value = goalManager[key]

            goalManager[key + "Changed"].connect(() => {
                                                     value = goalManager[key]
                                                 })
        }

        stepSize: 5

        snapMode: "SnapAlways"
    }
}
