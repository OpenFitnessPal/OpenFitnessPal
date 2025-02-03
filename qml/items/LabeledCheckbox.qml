import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

import QtMultimedia

import OpenFitnessPal

CheckBox {
    required property string label

    /** what property to bind to */
    required property string bindedProperty

    /** the target to bind the property to */
    required property var bindTarget

    font.pixelSize: 18 * Constants.scalar

    Component.onCompleted: checked = bindTarget[bindedProperty]
    onCheckedChanged: {
        bindTarget[bindedProperty] = checked
    }

    text: label
}
