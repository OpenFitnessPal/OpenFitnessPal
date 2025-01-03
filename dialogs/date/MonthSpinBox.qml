import QtQuick

import OpenFitnessPal

LabeledSpinBox {
    id: spinBox
    // /** what property to bind to */
    // required property string bindedProperty

    // /** the target to bind the property to */
    // required property var bindTarget

    font.pixelSize: 18 * Constants.scalar

    property var items: [
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December",
    ]

    from: 0
    to: items.length - 1

    editable: false

    label: "Month"

    textFromValue: function(value) {
        return items[value];
    }
}
