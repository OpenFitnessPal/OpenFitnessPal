import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

import QtMultimedia

import OpenFitnessPal

TextField {
    /** what property to bind to */
    required property string bindedProperty

    /** the target to bind the property to */
    required property var bindTarget

    id: textField
    font.pixelSize: 18 * Constants.scalar

    color: Constants.text

    text: bindTarget[bindedProperty]
    onEditingFinished: bindTarget[bindedProperty] = text

    renderType: TextInput.NativeRendering

    background: Rectangle {
        color: Constants.bg
        width: parent.width
        border.color: Constants.text
        border.width: 2 * Constants.scalar
        radius: 5 * Constants.scalar
    }
}
