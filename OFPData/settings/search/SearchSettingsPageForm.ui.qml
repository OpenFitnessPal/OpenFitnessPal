

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
    property alias add: add

    property alias generics: generics
    property alias results: results
    property alias filters: filters

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
        anchors.top: remove.bottom
        anchors.bottom: parent.bottom

        anchors.topMargin: 8
        anchors.leftMargin: 8
        anchors.rightMargin: 8
        anchors.bottomMargin: 8

        CheckBox {
            id: generics

            text: qsTr("Prefer Generics?")
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            Layout.fillWidth: true

            font: Constants.largeFont

            indicator.width: 32
            indicator.height: 32
        }

        RowLayout {
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            Layout.fillWidth: true
            Text {
                color: "#ffffff"
                text: "Results:"

                font: Constants.largeFont
            }

            SpinBox {
                id: results

                value: 10
                from: 1
                wrap: true
                editable: true

                Layout.fillWidth: true
                Layout.minimumHeight: 52

                font: Constants.largeFont
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            Text {
                color: "#ffffff"
                text: "Nutrient Filters"

                font: Constants.largeFont
            }

            AddButton {
                id: add

                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter

                Layout.minimumWidth: 51
            }
        }

        ListView {
            id: filters
            clip: true

            boundsMovement: Flickable.StopAtBounds
            boundsBehavior: Flickable.StopAtBounds
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}
