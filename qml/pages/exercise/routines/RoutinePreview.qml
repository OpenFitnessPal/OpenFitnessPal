import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

MouseArea {
    signal deleteRequested

    hoverEnabled: true
    onHoveredChanged: rct.color = containsMouse ? Constants.buttonHighlighted : Constants.button

    implicitHeight: 75 * Constants.scalar

    Rectangle {
        id: rct
        color: Constants.button
        anchors.fill: parent

        RowLayout {
            anchors.fill: parent
            anchors.margins: 8 * Constants.scalar

            IconButton {
                label: "Delete"
                onClicked: deleteRequested()
            }

            ColumnLayout {
                Layout.fillWidth: true
                Text {
                    font.pixelSize: 25 * Constants.scalar
                    color: Constants.text
                    text: model.name
                }

                Text {
                    font.pixelSize: 18 * Constants.scalar
                    color: "#A0A0A0"
                    text: model.notes
                }
            }

            Image {
                source: "qrc:/Forward"
                Layout.preferredWidth: 35 * Constants.scalar
                Layout.preferredHeight: 35 * Constants.scalar

                Layout.alignment: Qt.AlignRight
            }
        }
    }
}
