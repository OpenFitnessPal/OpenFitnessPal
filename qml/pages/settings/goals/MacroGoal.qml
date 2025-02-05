import QtQuick
import QtQuick.Controls.Universal
import QtQuick.Layouts

import OpenFitnessPal

ColumnLayout {
    required property string label
    required property string key
    required property int defaultValue

    property int caloriesPerGram: 4

    property int value: goalManager.get(key, defaultValue)

    property color handleColor: "red"

    onValueChanged: {
        recalc()
    }

    function recalc() {
        let calories = goalManager.get("calories", 3000)
        gramPreview.text = Math.round(
                    (value / 100.0) * (calories / caloriesPerGram)) + "g"
    }

    function accept() {
        goalManager.set(key, value)
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

        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    Text {
        text: slider.value + "%"

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
        value: parent.value

        onValueChanged: parent.value = value

        stepSize: 5

        snapMode: "SnapAlways"
    }
}
