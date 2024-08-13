import QtQuick 2.15
import QtQuick.Controls 2.15


import OFPData
import QtQuick.Layouts

Rectangle {
    id: exerciseSetForm

    width: 435
    height: 60

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
        anchors.leftMargin: 8
        anchors.rightMargin: 8
        anchors.topMargin: 4
        anchors.bottomMargin: 4

        // TODO: Swipe to delete ?
        RemoveButton {
            id: remove

            Layout.column: 0
            Layout.fillHeight: false
        }

        Text {
            id: staticText

            color: "#ffffff"
            text: qsTr("Reps:")

            Layout.column: 1

            font: Constants.mediumFont
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        SpinBox {
            id: repsEdit
            editable: true
            Layout.fillWidth: true

            Layout.column: 2

            font: Constants.tinyFont
        }

        Text {
            id: staticText1

            color: "#ffffff"
            text: qsTr("Weight:")

            Layout.column: 3

            font: Constants.mediumFont

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        SpinBox {
            id: weightEdit
            editable: true
            Layout.fillWidth: true

            Layout.column: 4

            to: 2000
            font: Constants.tinyFont
        }
    }
}
