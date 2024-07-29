import QtQuick 2.15
import QtQuick.Controls 2.15

SpinBox {
    from: 0
    to: items.length - 1
    value: 2 // maintain
    editable: false

    property var items: ["Fast Weight Loss", "Slow Weight Loss",
        "Maintain Weight", "Slow Weight Gain", "Fast Weight Gain"]

    validator: RegularExpressionValidator {
        regularExpression: new RegExp(
                               "(Fast Weight Gain|Slow Weight Gain|Maintain Weight|Slow Weight Loss|Fast Weight Loss)", "i")
    }

    textFromValue: function(value) {
        return items[value];
    }

    valueFromText: function(text) {
        for (var i = 0; i < items.length; ++i) {
            if (items[i].toLowerCase().indexOf(text.toLowerCase()) === 0)
                return i
        }
        return sb.value
    }
}
