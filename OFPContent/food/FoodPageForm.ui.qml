

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
    y: 0
    width: Constants.width
    height: Constants.pageHeight
    color: Constants.baseColor

    property date currentDate

    property alias mealLog1: mealLog1
    property alias mealLog2: mealLog2
    property alias mealLog3: mealLog3
    property alias mealLog4: mealLog4
    property alias mealLog5: mealLog5

    Text {
        id: text1

        color: "#ffffff"
        text: qsTr("Journal")
        anchors.top: parent.top
        anchors.topMargin: 8
        font.pixelSize: 24
        anchors.horizontalCenter: parent.horizontalCenter
        font.bold: true
    }

    ScrollView {
        id: scrollView
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: text1.bottom
        anchors.bottom: parent.bottom
        anchors.leftMargin: 0
        anchors.rightMargin: 0
        anchors.topMargin: 60
        anchors.bottomMargin: 40

        ColumnLayout {
            id: colLayout
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.leftMargin: 0
            anchors.rightMargin: 0
            anchors.topMargin: 0
            anchors.bottomMargin: 0
            spacing: 10

            MealLogImpl {
                id: mealLog1
                Layout.minimumHeight: 60
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                Layout.row: 0

                Layout.preferredHeight: 100 + listView.count * (100 + listView.spacing)
            }

            MealLogImpl {
                id: mealLog2
                Layout.minimumHeight: 60
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                Layout.row: 1

                Layout.preferredHeight: 100 + listView.count * (100 + listView.spacing)
            }

            MealLogImpl {
                id: mealLog3
                Layout.minimumHeight: 60
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                Layout.row: 2

                Layout.preferredHeight: 100 + listView.count * (100 + listView.spacing)
            }

            MealLogImpl {
                id: mealLog4
                Layout.minimumHeight: 60
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                Layout.row: 3

                Layout.preferredHeight: 100 + listView.count * (100 + listView.spacing)
            }

            MealLogImpl {
                id: mealLog5
                Layout.minimumHeight: 60
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                Layout.row: 4

                Layout.preferredHeight: 100 + listView.count * (100 + listView.spacing)
            }
        }
    }
}
