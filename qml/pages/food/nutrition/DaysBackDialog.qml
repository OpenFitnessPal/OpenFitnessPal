import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

AnimatedDialog {
    signal select(int selection, string label)

    id: dia
    title: "View"

    width: 300 * Constants.scalar

    property int selection: 0
    property string label

    property list<int> daysBack: [1, 7, 31]

    standardButtons: Dialog.Cancel | Dialog.Ok

    ColumnLayout {
        anchors.fill: parent
        Repeater {
            id: rep
            model: ["Today", "Past Week", "Past Month"]

            RadioButton {
                implicitHeight: 30 * Constants.scalar
                Layout.fillWidth: true

                text: modelData

                font.pixelSize: 16 * Constants.scalar

                Component.onCompleted: {
                    if (index === 0)
                        checked = true
                    contentItem.elide = Text.ElideRight
                }

                onCheckedChanged: if (checked) {
                                      dia.selection = daysBack[index]
                                      dia.label = modelData
                                  }
            }
        }
    }

    onAccepted: select(selection, label)
}
