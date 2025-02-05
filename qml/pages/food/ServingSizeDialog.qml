import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

AnimatedDialog {
    signal select(var selection)

    id: dia
    title: "Serving Size"

    width: 300 * Constants.scalar

    property var selection

    required property var model

    standardButtons: Dialog.Cancel | Dialog.Ok

    ColumnLayout {
        anchors.fill: parent
        Repeater {
            id: rep
            model: dia.model

            RadioButton {
                implicitHeight: 30 * Constants.scalar
                Layout.fillWidth: true

                text: model.name

                font.pixelSize: 16 * Constants.scalar

                Component.onCompleted: {
                    if (index === 0)
                        checked = true
                    contentItem.elide = Text.ElideRight
                }

                onCheckedChanged: if (checked) {
                                      dia.selection = model.size
                                  }
            }
        }
    }

    onAccepted: select(selection)
}
