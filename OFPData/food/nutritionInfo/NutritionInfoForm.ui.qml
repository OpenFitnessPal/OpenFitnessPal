

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
    width: Constants.width
    height: Constants.height
    visible: true
    color: Constants.sub1Color

    signal closeOut()

    property alias cal: cal
    property alias carbs: carbs
    property alias fiber: fiber
    property alias sugar: sugar
    property alias fat: fat
    property alias sat: sat
    property alias mono: mono
    property alias poly: poly
    property alias trans: trans
    property alias protein: protein
    property alias cholesterol: cholesterol
    property alias sodium: sodium
    property alias potassium: potassium
    property alias vitaminA: vitaminA
    property alias vitaminC: vitaminC
    property alias calcium: calcium
    property alias iron: iron

    property alias header: header

    NutritionInfoHeader {
        id: header
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
    }

    ScrollView {
        anchors.top: header.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        ColumnLayout {
            anchors.fill: parent

            NutritionGoal {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                name: "Calories"
                internalName: "calories"
                suffix: "kcal"

                id: cal
            }

            NutritionGoal {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                name: "Carbohydrates"
                internalName: "carbs"
                suffix: "g"

                isPercent: true

                id: carbs
            }

            NutritionGoal {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                name: "Fiber"
                internalName: "fiber"
                suffix: "g"

                id: fiber
            }

            NutritionGoal {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                name: "Sugar"
                internalName: "sugar"
                suffix: "g"

                id: sugar
            }

            NutritionGoal {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                name: "Fat"
                internalName: "fat"
                suffix: "g"

                isPercent: true
                isFat: true

                id: fat
            }

            NutritionGoal {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                name: "Saturated Fat"
                internalName: "sat"
                suffix: "g"

                id: sat
            }

            NutritionGoal {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                name: "Monounsturated Fat"
                internalName: "mono"
                suffix: "g"

                id: mono
            }

            NutritionGoal {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                name: "Polyunsaturated Fat"
                internalName: "poly"
                suffix: "g"

                id: poly
            }

            NutritionGoal {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                name: "Trans Fat"
                internalName: "trans"
                suffix: "g"

                id: trans
            }

            NutritionGoal {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                name: "Protein"
                internalName: "protein"
                suffix: "g"

                isPercent: true

                id: protein
            }

            NutritionGoal {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                name: "Cholesterol"
                internalName: "cholesterol"
                suffix: "mg"

                id: cholesterol
            }

            NutritionGoal {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                name: "Sodium"
                internalName: "sodium"
                suffix: "mg"

                id: sodium
            }

            NutritionGoal {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                name: "Potassium"
                internalName: "potassium"
                suffix: "mg"

                id: potassium
            }

            NutritionGoal {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                name: "Vitamin A"
                internalName: "vitaminA"
                suffix: "%"

                id: vitaminA
            }

            NutritionGoal {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                name: "Vitamin C"
                internalName: "vitaminC"
                suffix: "%"

                id: vitaminC
            }

            NutritionGoal {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                name: "Calcium"
                internalName: "calcium"
                suffix: "%"

                id: calcium
            }

            NutritionGoal {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                name: "Iron"
                internalName: "iron"
                suffix: "%"

                id: iron
            }
        }
    }
}
