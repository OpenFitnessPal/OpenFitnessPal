import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

RowLayout {
    signal pickDate

    property date currentDate: dateManager.date

    NavButton {
        Layout.preferredWidth: 40 * Constants.scalar
        Layout.preferredHeight: 40 * Constants.scalar
        Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter

        label: "Back"
        onClicked: {
            let newDate = currentDate

            newDate.setUTCDate(currentDate.getUTCDate() - 1)

            dateManager.date = newDate
        }
    }

    MouseArea {
        Layout.fillHeight: true
        Layout.fillWidth: true

        Text {
            anchors.fill: parent

            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: Math.round(32 * Constants.scalar)

            color: Constants.text

            text: (currentDate.getMonth() + 1) + "/" + currentDate.getDate(
                      ) + "/" + currentDate.getFullYear()
        }

        onClicked: pickDate()
    }

    NavButton {
        Layout.preferredWidth: 40 * Constants.scalar
        Layout.preferredHeight: 40 * Constants.scalar
        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter

        label: "Forward"
        onClicked: {
            let newDate = currentDate

            newDate.setUTCDate(currentDate.getUTCDate() + 1)

            dateManager.date = newDate
        }
    }
}
