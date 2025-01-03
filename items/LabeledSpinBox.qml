import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

import QtMultimedia

import OpenFitnessPal

SpinBox {
    id: spin
    required property string label

    /** what property to bind to */
    required property string bindedProperty

    /** the target to bind the property to */
    required property var bindTarget

    font.pixelSize: 18

    from: 0
    to: 1E9

    value: bindTarget[bindedProperty]
    onValueChanged: {
        bindTarget[bindedProperty] = value
    }

    contentItem: TextInput {
        text: parent.textFromValue(parent.value, parent.locale)

        font: parent.font
        color: Constants.text

        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter

        readOnly: !parent.editable

        inputMethodHints: Qt.ImhFormattedNumbersOnly

        onEditingFinished: spin.value = parseInt(text.replace(/,/g, ""))
    }

    up.indicator: Rectangle {
        x: spin.mirrored ? 0 : parent.width - width
        height: parent.height
        implicitWidth: 40
        implicitHeight: 40
        color: Constants.bg
        border.color: Constants.text

        Text {
            text: "+"
            font.pixelSize: spin.font.pixelSize * 2
            color: Constants.text
            anchors.fill: parent
            fontSizeMode: Text.Fit
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

    down.indicator: Rectangle {
        x: spin.mirrored ? parent.width - width : 0
        height: parent.height
        implicitWidth: 40
        implicitHeight: 40
        color: Constants.bg
        border.color: Constants.text

        Text {
            text: "-"
            font.pixelSize: spin.font.pixelSize * 2
            color: Constants.text
            anchors.fill: parent
            fontSizeMode: Text.Fit
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

    background: Rectangle {
        color: Constants.bg
        width: parent.width
        border.color: Constants.text
        border.width: 2
        radius: 5
    }

    Text {
        id: floatingLabel
        text: label
        color: Constants.text

        font.pixelSize: 15

        anchors {
            left: spin.left
            bottom: spin.top

            bottomMargin: -2
            leftMargin: 10
        }
    }
}
