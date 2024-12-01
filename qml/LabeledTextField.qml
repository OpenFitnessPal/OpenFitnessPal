import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

TextField {
    required property string label

    /** any of: string, int, double */
    property string type: "string"

    id: textField

    color: "white"

    property var value

    onTextChanged: {
        switch (type) {
        case "string":
            value = text
            break
        case "int":
            value = parseInt(text)
            break
        case "double":
            value = parseDouble(text)
            break
        default:
            break
        }
    }

    background: Rectangle {
        color: Constants.sub3Color
        width: parent.width
        border.color: "white"
        border.width: 2
        radius: 5
    }

    Text {
        id: floatingLabel
        text: label
        color: "white"

        font.pixelSize: 15

        anchors {
            left: textField.left
            bottom: textField.top

            bottomMargin: -2
            leftMargin: 10
        }
    }

    validator: RegularExpressionValidator {
        regularExpression: {
            switch (type) {
            case "double":
                return /^\d*\.?\d*$/
            case "int":
                                return /^[-+]?[1-9]\d*$/
            default:

            case "string":
                return /.*/
            }
        }
    }
}
