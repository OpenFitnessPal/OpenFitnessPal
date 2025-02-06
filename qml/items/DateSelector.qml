import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

RowLayout {
    signal pickDate

    property date currentDate: new Date()

    Component.onCompleted: {
        let newDate = new Date()
        // slightly hacky way to ensure the timezone is correct
        newDate.setUTCMinutes(newDate.getUTCMinutes(
                                  ) - newDate.getTimezoneOffset())

        currentDate = newDate
    }

    onCurrentDateChanged: {
        mealNamesModel.date = currentDate
    }

    NavButton {
        Layout.preferredWidth: 40 * Constants.scalar
        Layout.preferredHeight: 40 * Constants.scalar
        Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter

        label: "Back"
        onClicked: currentDate.setUTCDate(currentDate.getUTCDate() - 1)
    }

    MouseArea {
        Layout.fillHeight: true
        Layout.fillWidth: true

        Text {
            anchors.fill: parent

            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: Math.round(32 * Constants.scalar)

            color: Constants.text

            text: (currentDate.getUTCMonth(
                       ) + 1) + "/" + currentDate.getUTCDate(
                      ) + "/" + currentDate.getUTCFullYear()
        }

        onClicked: pickDate()
    }

    NavButton {
        Layout.preferredWidth: 40 * Constants.scalar
        Layout.preferredHeight: 40 * Constants.scalar
        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter

        label: "Forward"
        onClicked: currentDate.setUTCDate(currentDate.getUTCDate() + 1)
    }
}
