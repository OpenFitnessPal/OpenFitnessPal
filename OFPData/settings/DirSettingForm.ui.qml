

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

RowLayout {
    required property bool isCache

    property alias dir: dir
    property alias button: button

    Text {
        id: dirText
        color: "#ffffff"
        text: qsTr((isCache ? "Cache" : "Data") + " Directory:")

        anchors.leftMargin: 20
        anchors.topMargin: 10

        font: Constants.underlinedMediumFont
    }

    TextField {
        id: dir
        height: 35
        color: "#ffffff"

        font: Constants.mediumFont
        Layout.fillWidth: true
    }

    ToolButton {
        id: button
        height: 35
        text: "Select..."
    }
}
