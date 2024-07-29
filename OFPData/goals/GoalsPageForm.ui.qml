

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
    id: rectangle
    width: Constants.width
    height: Constants.pageHeight
    color: Constants.baseColor

    property alias recalc: recalc
    property alias goal: goal
    property alias weight: weight
    property alias calories: calories
    property alias macros: macros

    Text {
        id: text1
        color: "#ffffff"
        text: qsTr("Goals")
        anchors.top: parent.top
        anchors.topMargin: 8
        font.pixelSize: 24
        font.bold: true
        anchors.horizontalCenter: parent.horizontalCenter
    }

    ScrollView {
        id: scroll

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: text1.bottom
        anchors.bottom: parent.bottom

        anchors.leftMargin: 0
        anchors.rightMargin: 0
        anchors.topMargin: 8
        anchors.bottomMargin: 40

        ColumnLayout {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.leftMargin: 0
            anchors.rightMargin: 0
            anchors.topMargin: 0
            anchors.bottomMargin: 0

            IntGoalImpl {
                id: weight
                value: 135

                isRootItem: true

                name: "Current Weight"
                Layout.fillWidth: true
                internalName: "weight"
                suffix: "lbs"

                max: 10000
            }

            WeightGoal {
                id: goal

                Layout.leftMargin: 8
                Layout.fillWidth: true
            }

            IntGoalImpl {
                id: calories
                value: 2500

                isRootItem: true

                name: "Target Calories"
                Layout.fillWidth: true
                internalName: "calories"
                suffix: "kcal"

                max: 10000
            }

            ToolButton {
                id: recalc
                text: "Recalculate Goals"
                font.pointSize: 16
                highlighted: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            }

            MacroGoals {
                id: macros
                width: 450
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

            IntGoalImpl {
                id: calcium
                value: 100

                isRootItem: true

                name: "Calcium"
                Layout.fillWidth: true
                internalName: "calcium"
                suffix: "%"

                max: 10000
            }

            IntGoalImpl {
                id: iron
                value: 100

                isRootItem: true

                name: "Iron"
                Layout.fillWidth: true
                internalName: "iron"
                suffix: "%"

                max: 10000
            }

            IntGoalImpl {
                id: vitaminA
                value: 100

                isRootItem: true

                name: "Vitamin A"
                Layout.fillWidth: true
                internalName: "vitaminA"
                suffix: "%"

                max: 10000
            }

            IntGoalImpl {
                id: vitaminC
                value: 100

                isRootItem: true

                name: "Vitamin C"
                Layout.fillWidth: true
                internalName: "vitaminC"
                suffix: "%"

                max: 10000
            }

            IntGoalImpl {
                id: vitaminD
                value: 100

                isRootItem: true

                name: "Vitamin D"
                Layout.fillWidth: true
                internalName: "vitaminD"
                suffix: "%"

                max: 10000
            }

            IntGoalImpl {
                id: sodium
                value: 6000

                isRootItem: true

                name: "Sodium"
                Layout.fillWidth: true
                internalName: "sodium"
                suffix: "mg"

                max: 100000
            }

            IntGoalImpl {
                id: potassium
                value: 4000

                isRootItem: true

                name: "Potassium"
                Layout.fillWidth: true
                internalName: "potassium"
                suffix: "mg"

                max: 100000
            }

            IntGoalImpl {
                id: cholesterol
                value: 600

                isRootItem: true

                name: "Cholesterol"
                Layout.fillWidth: true
                internalName: "cholesterol"
                suffix: "mg"

                max: 100000
            }
        }
    }
}
