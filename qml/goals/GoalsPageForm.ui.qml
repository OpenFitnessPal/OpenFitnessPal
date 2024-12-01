

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15

import OpenFitnessPal
import QtQuick.Layouts

Rectangle {
    id: rectangle
    width: Constants.width
    height: Constants.pageHeight
    color: Constants.baseColor

    signal changeNutrition

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
        font: Constants.titleFont

        anchors.horizontalCenter: parent.horizontalCenter
    }

    ScrollView {
        id: scroll

        contentWidth: availableWidth

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: text1.bottom
        anchors.bottom: parent.bottom

        anchors.leftMargin: 0
        anchors.rightMargin: 0
        anchors.topMargin: 8
        anchors.bottomMargin: 50

        ColumnLayout {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.leftMargin: 0
            anchors.rightMargin: 0
            anchors.topMargin: 0
            anchors.bottomMargin: 0

            IntGoal {
                id: weight
                value: 135

                isRootItem: true

                name: "Current Weight (lbs)"
                Layout.fillWidth: true
                internalName: "weight"
                suffix: ""

                max: 10000
            }

            WeightGoal {
                id: goal

                Layout.leftMargin: 8
                Layout.fillWidth: true
            }

            IntGoal {
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
                font: Constants.mediumFont
                highlighted: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            }

            MacroGoals {
                id: macros
                width: 450
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

            IntGoal {
                id: calcium
                value: 100

                isRootItem: true

                name: "Calcium"
                Layout.fillWidth: true
                internalName: "calcium"
                suffix: "%"
                defaultValue: 100

                max: 10000
            }

            IntGoal {
                id: iron
                value: 100

                isRootItem: true

                name: "Iron"
                Layout.fillWidth: true
                internalName: "iron"
                suffix: "%"
                defaultValue: 100

                max: 10000
            }

            IntGoal {
                id: vitaminA
                value: 100

                isRootItem: true

                name: "Vitamin A"
                Layout.fillWidth: true
                internalName: "vitaminA"
                suffix: "%"
                defaultValue: 100

                max: 10000
            }

            IntGoal {
                id: vitaminC
                value: 100

                isRootItem: true

                name: "Vitamin C"
                Layout.fillWidth: true
                internalName: "vitaminC"
                suffix: "%"
                defaultValue: 100

                max: 10000
            }

            IntGoal {
                id: vitaminD
                value: 100

                isRootItem: true

                name: "Vitamin D"
                Layout.fillWidth: true
                internalName: "vitaminD"
                suffix: "%"
                defaultValue: 100

                max: 10000
            }

            IntGoal {
                id: sodium
                value: 6000

                isRootItem: true

                name: "Sodium"
                Layout.fillWidth: true
                internalName: "sodium"
                suffix: "mg"
                defaultValue: 6000

                max: 100000
            }

            IntGoal {
                id: potassium
                value: 4000

                isRootItem: true

                name: "Potassium"
                Layout.fillWidth: true
                internalName: "potassium"
                suffix: "mg"
                defaultValue: 4000

                max: 100000
            }

            IntGoal {
                id: cholesterol
                value: 600

                isRootItem: true

                name: "Cholesterol"
                Layout.fillWidth: true
                internalName: "cholesterol"
                suffix: "mg"
                defaultValue: 600

                max: 100000
            }
        }
    }
}
