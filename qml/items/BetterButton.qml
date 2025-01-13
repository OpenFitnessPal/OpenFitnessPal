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
    Layout.preferredHeight: 40 * Constants.scalar
    Layout.alignment: Qt.AlignTop

    MouseArea {
        hoverEnabled: true
        onHoveredChanged: parent.color
                          = containsMouse ? Constants.buttonHighlighted : Constants.button

        onClicked: parent.clicked()

        anchors.fill: parent

        RowLayout {
            anchors.fill: parent
            Text {
                font.pixelSize: Math.round(18 * Constants.scalar)
                color: Constants.text
                text: name

                Layout.leftMargin: 20 * Constants.scalar
            }

            Image {
                source: "qrc:/Forward"
                Layout.preferredHeight: 35 * Constants.scalar
                Layout.preferredWidth: 35 * Constants.scalar

                Layout.alignment: Qt.AlignRight
            }
        }
    }
}
