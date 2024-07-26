

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15

import OFPData
import QtQuick.Layouts

Rectangle {
    id: root

    color: Constants.sub1Color

    property bool isValid: true

    property int fontSize: 18
    property int name: "Goal Name"

    property alias spinBox: spinBox

    width: 480
    height: 80

    RowLayout {
        id: rowLayout
        anchors.fill: parent
        anchors.leftMargin: 8
        anchors.rightMargin: 8
        anchors.topMargin: 8
        anchors.bottomMargin: 8

        Text {
            id: goalName
            color: isValid ? "#ffffff" : "#ffff00"

            Layout.row: 0

            text: qsTr(name)
            font.pixelSize: fontSize
            Layout.fillHeight: false
        }

        PercentageBox {
            id: spinBox
            editable: true

            Layout.fillHeight: true
            Layout.fillWidth: true

            Layout.row: 1
        }
    }
}
