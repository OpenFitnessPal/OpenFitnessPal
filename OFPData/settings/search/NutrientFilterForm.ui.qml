

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
    width: 400
    height: 60

    color: Constants.sub1Color
    border.color: "#ffffff"
    border.width: 2

    property alias remove: remove
    property alias name: name
    property alias threshold: threshold

    RowLayout {
        anchors.fill: parent

        anchors.leftMargin: 8
        anchors.rightMargin: 8
        anchors.topMargin: 8
        anchors.bottomMargin: 8

        RemoveButton {
            id: remove
            Layout.maximumHeight: 42
        }

        Text {
            id: name

            text: qsTr(displayName)

            color: "#ffffff"
            font: Constants.mediumFont
        }

        DoubleSpinBox {
            id: threshold
            value: filter * 100.0
            stepSize: 10
            suffix: model.suffix

            font: Constants.mediumFont

            Layout.fillWidth: true
        }
    }
}
