import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

AnimatedDialog {
    signal resetGoal(int carbs, int fat, int protein)

    id: dia
    title: "Macro Presets"

    width: 300 * Constants.scalar

    property int carbs
    property int fat
    property int protein

    standardButtons: Dialog.Cancel | Dialog.Ok

    ListModel {
        id: presetModel

        ListElement {
            name: "Custom"
            carbs: 0
            fat: 0
            protein: 0
        }

        ListElement {
            name: "Keto"
            carbs: 5
            fat: 75
            protein: 20
        }

        ListElement {
            name: "Athletic"
            carbs: 50
            fat: 30
            protein: 20
        }
    }

    ColumnLayout {
        anchors.fill: parent
        Repeater {
            id: rep
            model: presetModel

            RadioButton {
                implicitHeight: 30 * Constants.scalar
                text: model.name

                font.pixelSize: 18 * Constants.scalar

                Component.onCompleted: if (index === 0)
                                           checked = true

                onCheckedChanged: if (checked) {
                                      dia.carbs = model.carbs
                                      dia.fat = model.fat
                                      dia.protein = model.protein
                                  }
            }
        }
    }

    onAccepted: resetGoal(carbs, fat, protein)
}
