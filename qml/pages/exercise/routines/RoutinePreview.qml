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
            spacing: 0

            IconButton {
                label: "Delete"
                onClicked: deleteRequested()

                Layout.maximumWidth: 40 * Constants.scalar
            }

            ColumnLayout {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter

                Text {
                    Layout.fillWidth: true
                    font.pixelSize: 25 * Constants.scalar
                    color: Constants.text
                    text: model.name

                    elide: Text.ElideRight
                }

                Text {
                    Layout.fillWidth: true
                    font.pixelSize: 18 * Constants.scalar
                    color: "#A0A0A0"
                    text: model.notes

                    elide: Text.ElideRight
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
