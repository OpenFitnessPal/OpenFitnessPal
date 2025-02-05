import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

MouseArea {
    signal deleteRequested

    hoverEnabled: true

    implicitHeight: 75 * Constants.scalar

    Rectangle {
        id: rct
        color: containsMouse
               && !del.mousedOver ? Constants.buttonHighlighted : Constants.sub
        anchors.fill: parent

        RowLayout {
            anchors.fill: parent
            anchors.margins: 8 * Constants.scalar
            spacing: 10 * Constants.scalar

            NavButton {
                id: del
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
                    text: model.time + " min, " + model.cals + " kcal"

                    elide: Text.ElideRight
                }
            }
        }
    }
}
