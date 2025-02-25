import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

Rectangle {
    id: select

    property int daysBack: 1

    property int buttonHeight: 35
    property int fontSize: 14

    color: Constants.sub

    DaysBackDialog {
        id: backDialog

        onSelect: (selection, label) => {
                      viewLabel.text = label
                      select.daysBack = selection
                  }
    }

    implicitHeight: buttonHeight * Constants.scalar

    MouseArea {
        anchors.fill: parent
        onClicked: backDialog.open()

        RowLayout {
            anchors {
                fill: parent

                rightMargin: 10 * Constants.scalar
            }

            Text {
                id: viewLabel

                Layout.fillWidth: true

                color: Constants.text

                text: "Today"

                font.pixelSize: fontSize * Constants.scalar

                horizontalAlignment: Text.AlignHCenter
            }
        }
    }
}
