import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

MouseArea {
    signal deleteRequested

    hoverEnabled: true

    // implicitHeight: 65 * Constants.scalar
    property bool canBeDeleted: true

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

                visible: canBeDeleted

                Layout.maximumWidth: 40 * Constants.scalar
            }

            ColumnLayout {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter

                Text {
                    Layout.fillWidth: true

                    font.pixelSize: 18 * Constants.scalar
                    color: Constants.text
                    text: name

                    elide: Text.ElideRight
                }

                Text {
                    Layout.fillWidth: true

                    font.pixelSize: 14 * Constants.scalar
                    color: "#A0A0A0"
                    text: item.brand + ", " + model.size.unit(units)

                    elide: Text.ElideRight
                }
            }

            Text {
                font.pixelSize: 14 * Constants.scalar
                color: "#A0A0A0"
                text: Math.round(
                          item.nutrients.calories * model.size.multiplier(
                              units) * 10) / 10. + "kcal"

                elide: Text.ElideRight
            }
        }
    }

    Rectangle {
        color: "gray"

        height: 1

        anchors {
            bottom: parent.bottom

            left: parent.left
            right: parent.right
        }
    }
}
