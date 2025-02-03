import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

AnimatedDialog {
    signal resetGoal(int idx, string result)

    id: dia
    title: "Weight Goal"

    property int idx
    property string text

    standardButtons: Dialog.Cancel | Dialog.Ok

    ColumnLayout {
        anchors.fill: parent
        Repeater {
            id: rep
            model: ["Fast Weight Loss", "Slow Weight Loss", "Maintain Weight", "Slow Weight Gain", "Fast Weight Gain"]

            RadioButton {
                implicitHeight: 30 * Constants.scalar
                text: modelData

                font.pixelSize: 18 * Constants.scalar

                checked: index === goalManager.get("goal", 2)

                onCheckedChanged: if (checked) {
                                      dia.idx = index
                                      dia.text = modelData
                                  }
            }
        }
    }

    onAccepted: resetGoal(idx, text)
}
