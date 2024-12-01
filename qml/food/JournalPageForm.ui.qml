import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

import OpenFitnessPal

Rectangle {
    color: Constants.baseColor

    signal nutritionInfoRequested

    property alias mealLog1: mealLog1
    property alias mealLog2: mealLog2
    property alias mealLog3: mealLog3
    property alias mealLog4: mealLog4
    property alias mealLog5: mealLog5

    property alias calPreview: calPreview

    ScrollView {
        id: scroll

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 8

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

            CaloriePreview {
                id: calPreview
                // width: Layout.width
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

            MealLog {
                id: mealLog1
                Layout.minimumHeight: 60
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                Layout.row: 0

                Layout.preferredHeight: 100 + listView.count * (100 + listView.spacing)
            }

            MealLog {
                id: mealLog2
                Layout.minimumHeight: 60
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                Layout.row: 1

                Layout.preferredHeight: 100 + listView.count * (100 + listView.spacing)
            }

            MealLog {
                id: mealLog3
                Layout.minimumHeight: 60
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                Layout.row: 2

                Layout.preferredHeight: 100 + listView.count * (100 + listView.spacing)
            }

            MealLog {
                id: mealLog4
                Layout.minimumHeight: 60
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                Layout.row: 3

                Layout.preferredHeight: 100 + listView.count * (100 + listView.spacing)
            }

            MealLog {
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
