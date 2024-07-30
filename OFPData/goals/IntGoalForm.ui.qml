

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

    signal goalValueChanged(int value)

    property bool isRootItem: true
    property bool isValid: true

    property string name: "Goal Name"
    property string internalName: "goal"
    property string suffix: "%"

    property int max: 100
    property int value

    property alias spinBox: spinBox

    color: isRootItem ? Constants.baseColor : Constants.sub1Color

    property font myFont: isRootItem ? Constants.mediumFont : Constants.smallFont

    width: 480
    height: isRootItem ? 40 : 35

    Text {
        id: goalName
        color: isValid ? "#ffffff" : "#ffff00"

        text: qsTr(name + ":")

        anchors.left: parent.left
        anchors.right: parent.horizontalCenter
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        anchors.leftMargin: 8
        anchors.rightMargin: 8
        anchors.topMargin: 4
        anchors.bottomMargin: 4

        font: myFont
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
    }

    SuffixedSpinBox {
        id: spinBox
        editable: true
        to: max
        suffix: root.suffix
        value: root.value

        anchors.right: parent.right
        anchors.left: parent.horizontalCenter
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        anchors.leftMargin: 8
        anchors.rightMargin: 8
        anchors.topMargin: 4
        anchors.bottomMargin: 4
    }
}

/*##^##
Designer {
    D{i:0;formeditorColor:"#00000c"}
}
##^##*/

