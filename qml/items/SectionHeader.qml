import QtQuick

import OpenFitnessPal

Column {
    width: parent.width

    /** What text to display */
    required property string label

    Text {
        font.pixelSize: 18 * Constants.scalar
        font.bold: true
        color: Constants.text
        text: label
    }
}
