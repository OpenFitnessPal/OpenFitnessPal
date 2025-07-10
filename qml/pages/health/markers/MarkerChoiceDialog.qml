import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

AnimatedDialog {
    signal choice(string coice)

    id: dia
    title: "Health Marker"

    width: 300 * Constants.scalar

    property string key

    property bool raw: false

    standardButtons: Dialog.Cancel | Dialog.Ok

    ColumnLayout {
        anchors.fill: parent
        Repeater {
            id: rep
            model: raw ? healthMarkerModel.rawOptions(
                             ) : healthMarkerModel.options

            RadioButton {
                implicitHeight: 30 * Constants.scalar
                text: modelData

                font.pixelSize: 18 * Constants.scalar

                Component.onCompleted: if (index === 0)
                                           checked = true

                onCheckedChanged: if (checked) {
                                      dia.key = modelData
                                  }
            }
        }
    }

    onAccepted: choice(key)
}
