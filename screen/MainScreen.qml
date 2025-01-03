import QtQuick
import QtQuick.Controls
import QtQuick.Layouts 6.6

import OpenFitnessPal

Rectangle {
    id: screen
    width: parent.width
    height: parent.height
    color: Constants.bg

    DateSelector {
        id: dateSelect

        anchors {
            top: parent.top
            left: parent.left
            right: parent.right

            margins: 4
        }

        onPickDate: {
            picker.currentDate = currentDate
            picker.open()
        }
    }

    DatePicker {
        id: picker

        onAccepted: {
            dateSelect.currentDate = currentDate
        }
    }
}
