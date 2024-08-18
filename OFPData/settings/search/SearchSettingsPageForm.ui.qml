

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

import OFPData

Rectangle {
    id: rectangle
    width: Constants.width
    height: Constants.pageHeight
    color: Constants.baseColor

    property alias remove: remove

    RemoveButton {
        id: remove

        anchors.left: parent.left
        anchors.top: parent.top

        anchors.leftMargin: 15
        anchors.topMargin: 8
    }

    Text {
        id: text1
        color: "#ffffff"

        font: Constants.titleFont
        text: "Search Settings"
        anchors.top: parent.top
        anchors.topMargin: 8
        anchors.horizontalCenter: parent.horizontalCenter
    }

    ColumnLayout {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: text1.bottom
        anchors.bottom: parent.bottom
        anchors.leftMargin: 8
        anchors.rightMargin: 8
        anchors.bottomMargin: 8

        CheckBox {
            id: checkBox
            text: qsTr("Prefer Generics?")
            Layout.fillWidth: true

            font: Constants.largeFont

            indicator.width: 32
            indicator.height: 32
        }

        RowLayout {
            Layout.fillWidth: true
            Text {
                color: "#ffffff"
                text: "Results:"

                font: Constants.largeFont
            }

            SpinBox {
                value: 10
                from: 1
                wrap: true
                editable: true

                Layout.fillWidth: true
                Layout.minimumHeight: 50

                font: Constants.largeFont
            }
        }
    }
}
