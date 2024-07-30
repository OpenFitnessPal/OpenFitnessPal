

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15

import OFPData

Rectangle {
    id: rectangle
    color: Constants.sub1Color
    border.color: "#ffffff"

    height: 100

    signal deleteRecipe(int id)

    property alias recipeName: recipeName
    property alias servingSize: servingSize
    property alias calories: calories
    property alias mouse: mouse
    property alias remove: remove

    MouseArea {
        anchors.fill: parent
        id: mouse

        Text {
            id: recipeName
            color: "#ffffff"
            text: qsTr("Recipe Name")
            anchors.left: remove.right
            anchors.top: parent.top
            anchors.leftMargin: 15
            anchors.topMargin: 15
            font: Constants.boldLargeFont
        }

        Text {
            id: servingSize
            color: "#c2c2c2"
            text: qsTr("1 serving")
            anchors.left: remove.right
            anchors.top: recipeName.bottom
            anchors.leftMargin: 25
            anchors.topMargin: 15
            font: Constants.tinyFont
        }

        Text {
            id: calories

            color: "#c2c2c2"
            text: qsTr("0kcal")
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 25
            font: Constants.mediumFont
        }

        RemoveButton {
            visible: false
            id: remove

            anchors.left: parent.left
            anchors.leftMargin: 8
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}
