import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

Rectangle {
    id: settingsButton

    signal clicked

    required property string name

    color: Constants.button

    Layout.fillWidth: true
    Layout.preferredHeight: 75 * Constants.scalar
    Layout.alignment: Qt.AlignTop

    Layout.leftMargin: 10
    Layout.rightMargin: 10

    MouseArea {
        hoverEnabled: true
        onHoveredChanged: parent.color
                          = containsMouse ? Constants.buttonHighlighted : Constants.button

        onClicked: parent.clicked()

        anchors.fill: parent

        RowLayout {
            anchors.fill: parent
            BigIcon {
                id: image
                label: name

                buttonHeight: 80
                buttonWidth: 80

                onClicked: settingsButton.clicked()
            }

            Text {
                font.pixelSize: Math.round(40 * Constants.scalar)
                color: Constants.text
                text: name
            }

            Image {
                source: "qrc:/Forward"
                Layout.alignment: Qt.AlignRight
            }
        }
    }
}
