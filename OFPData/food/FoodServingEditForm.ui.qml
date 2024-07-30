

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

    property alias submit: submit
    property alias back: back

    property alias foodName: foodName
    property alias servings: servings
    property alias unit: unit
    property alias calories: calories
    property alias carbs: carbs
    property alias fat: fat
    property alias protein: protein

    Button {
        id: back
        width: 50
        height: 50
        text: qsTr("<")
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 8
        anchors.topMargin: 0
        font.pointSize: 26
    }

    Button {
        id: submit
        width: 50
        height: 50
        text: qsTr(">")
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: 8
        anchors.topMargin: 0
        font.pointSize: 26
    }

    Text {
        id: title
        color: "#ffffff"
        text: qsTr("Edit")
        anchors.top: parent.top
        anchors.topMargin: 10
        font: Constants.titleFont

        anchors.horizontalCenter: parent.horizontalCenter
    }

    Text {
        id: foodName
        color: "#ffffff"
        text: qsTr("Food Name")
        anchors.left: parent.left
        anchors.top: title.bottom
        anchors.leftMargin: 40
        anchors.topMargin: 20
        font: Constants.boldSubtitleFont
        wrapMode: Text.WrapAnywhere
    }

    Text {
        id: text1
        color: "#ffffff"
        text: qsTr("Servings")
        anchors.left: foodName.left
        anchors.top: foodName.bottom
        anchors.leftMargin: 20
        anchors.topMargin: 30
        font: Constants.subSubtitleFont
    }

    Text {
        id: text2
        color: "#ffffff"
        text: qsTr("Unit")
        anchors.left: foodName.left
        anchors.top: text1.bottom
        anchors.leftMargin: 20
        anchors.topMargin: 30
        font: Constants.subSubtitleFont
    }

    DoubleSpinBox {
        id: servings
        anchors.left: title.left
        anchors.right: parent.right
        anchors.top: text1.top
        anchors.bottom: text1.bottom
        anchors.leftMargin: 0
        anchors.rightMargin: 15
        anchors.topMargin: -6
        anchors.bottomMargin: -6
        to: 1000 * 100
    }

    ComboBox {
        id: unit
        anchors.left: title.left
        anchors.right: parent.right
        anchors.top: text2.top
        anchors.bottom: text2.bottom
        anchors.leftMargin: 0
        anchors.rightMargin: 15
        anchors.topMargin: -6
        anchors.bottomMargin: -6
    }

    Text {
        id: text3
        color: "#ffffff"
        text: qsTr("Calories")
        anchors.left: parent.left
        anchors.top: text2.bottom
        anchors.leftMargin: 15
        anchors.topMargin: 50
        font: Constants.mediumSubtitleFont
    }

    Text {
        id: calories
        y: 303
        color: "#fdfdfd"
        text: qsTr("0kcal")
        anchors.top: text3.bottom
        anchors.topMargin: 25
        font: Constants.mediumFont
        anchors.horizontalCenter: text3.horizontalCenter
    }

    Text {
        id: text4
        color: "#ffffff"
        text: qsTr("Carbs")
        anchors.left: text3.right
        anchors.top: text3.top
        anchors.leftMargin: 60
        anchors.topMargin: 0
        font: Constants.mediumSubtitleFont
    }

    Text {
        id: carbs
        y: 303
        color: "#fdfdfd"
        text: qsTr("0g")
        anchors.top: text4.bottom
        anchors.topMargin: 25
        font: Constants.mediumFont
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: text4.horizontalCenter
    }

    Text {
        id: text5
        color: "#ffffff"
        text: qsTr("Fat")
        anchors.left: text4.right
        anchors.top: text3.top
        anchors.leftMargin: 60
        anchors.topMargin: 0
        font: Constants.mediumSubtitleFont
    }

    Text {
        id: fat
        y: 303
        color: "#fdfdfd"
        text: qsTr("0g")
        anchors.top: text5.bottom
        anchors.topMargin: 25
        font: Constants.mediumFont
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: text5.horizontalCenter
    }

    Text {
        id: text6
        color: "#ffffff"
        text: qsTr("Protein")
        anchors.left: text5.right
        anchors.top: text3.top
        anchors.leftMargin: 60
        anchors.topMargin: 0
        font: Constants.mediumSubtitleFont
    }

    Text {
        id: protein
        y: 303
        color: "#fdfdfd"
        text: qsTr("0g")
        anchors.top: text6.bottom
        anchors.topMargin: 25
        font: Constants.mediumFont
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: text6.horizontalCenter
    }
}
