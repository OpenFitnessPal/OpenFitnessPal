import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Shapes 2.15

import OpenFitnessPal

ComboBox {
    required property string label

    /** what property to bind to */
    required property string key

    required property int defaultValue

    /** choices for the combobox */
    required property var choices

    id: combo
    model: choices
    font.pixelSize: 15 * Constants.scalar

    implicitHeight: 40 * Constants.scalar

    currentIndex: goalManager.get(key, defaultValue)
    onCurrentIndexChanged: goalManager.set(key, currentIndex)

    delegate: ItemDelegate {
        id: delegate

        width: combo.width
        contentItem: Text {
            text: modelData
            color: Constants.text
            font.pixelSize: 15 * Constants.scalar
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
        }
        highlighted: combo.highlightedIndex === index
    }

    Text {
        id: floatingLabel
        text: label
        color: Constants.text

        font.pixelSize: 15 * Constants.scalar

        anchors {
            left: parent.left
            bottom: parent.top

            bottomMargin: -2
            leftMargin: 10 * Constants.scalar
        }
    }
}
