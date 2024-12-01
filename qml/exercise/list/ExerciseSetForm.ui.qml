import QtQuick 2.15
import QtQuick.Controls 2.15

import OpenFitnessPalContent
import QtQuick.Layouts

Rectangle {
    id: exerciseSetForm

    width: 435
    height: 70

    color: Constants.sub2Color
    border.color: "#ffffff"

    signal deleteSet(int myId)
    signal changed(int reps, int weight, int id)

    property alias remove: remove
    property alias repsEdit: repsEdit
    property alias weightEdit: weightEdit

    RowLayout {
        id: rowlayout
        anchors.fill: parent
        uniformCellSizes: true

        anchors.leftMargin: 8
        anchors.rightMargin: 8
        anchors.topMargin: 14
        anchors.bottomMargin: 4

        // TODO: Swipe to delete ?
        RemoveButton {
            id: remove

            Layout.fillHeight: false
        }

        LabeledTextField {
            id: repsEdit
            Layout.fillWidth: true

            label: "Reps"
            type: "int"

            font: Constants.tinyFont
        }

        LabeledTextField {
            id: weightEdit
            Layout.fillWidth: true

            label: "Weight"
            type: "int"

            font: Constants.tinyFont
        }
    }
}
