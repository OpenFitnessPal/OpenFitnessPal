import QtQuick
import QtQuick.Controls
import QtQml

Rectangle {
    id: root
    width: parent.width
    height: 40
    color: "#000000"

    signal dateChanged(var newDate)

    // TODO: DATE PICKER
    MouseArea {
        id: mouseArea
        width: dateText.width
        height: 36
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        Text {
            id: dateText
            property date currentDate: new Date()

            color: "#ffffff"
            text: currentDate.toLocaleDateString(Qt.locale(), "MM/dd/yyyy")
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 30
            anchors.verticalCenterOffset: 0
            anchors.horizontalCenterOffset: 0
            anchors.horizontalCenter: parent.horizontalCenter
        }

        onClicked: dateDialog.visible = true
    }

    Button {
        id: back

        width: 59
        height: 38
        text: qsTr("<")
        anchors.left: parent.left
        anchors.leftMargin: 0
        font.pointSize: 26

        onClicked: {
            dateText.currentDate.setDate(dateText.currentDate.getDate() - 1);
            dateChanged(dateText.currentDate)
        }
    }

    Button {
        id: next

        width: 59
        height: 38
        text: qsTr(">")
        anchors.right: parent.right
        anchors.rightMargin: 0
        font.pointSize: 26

        onClicked: {
            dateText.currentDate.setDate(dateText.currentDate.getDate() + 1);
            dateChanged(dateText.currentDate)
        }
    }
}


