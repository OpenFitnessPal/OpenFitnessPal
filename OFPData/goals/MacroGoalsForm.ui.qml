

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

Rectangle {
    id: rectangle

    // height: 450
    color: "#000000"

    property alias carbs: carbs
    property alias fat: fat
    property alias protein: protein

    ColumnLayout {
        anchors.fill: parent

        anchors.leftMargin: 8
        anchors.rightMargin: 8
        anchors.topMargin: 8
        anchors.bottomMargin: 8

        IntGoalImpl {
            id: carbs

            isRootItem: true

            name: "Carbohydrates"
            Layout.fillWidth: true
            internalName: "carbs"
            suffix: "%"

            max: 100 - fat.value - protein.value
        }

        ColumnLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.leftMargin: 30

            IntGoalImpl {
                id: fiber

                isRootItem: false

                name: "Fiber"
                Layout.fillWidth: true
                internalName: "fiber"
                suffix: "%"

                max: 100 - sugar.value
            }

            IntGoalImpl {
                id: sugar

                isRootItem: false

                name: "Sugar"
                Layout.fillWidth: true
                internalName: "sugar"
                suffix: "%"

                max: 100 - fiber.value
            }
        }

        IntGoalImpl {
            id: fat

            isRootItem: true

            name: "Fat"
            Layout.fillWidth: true
            internalName: "fat"
            suffix: "%"

            max: 100 - carbs.value - protein.value
        }

        ColumnLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.leftMargin: 30

            IntGoalImpl {
                id: satFat

                isRootItem: false

                name: "Saturated Fat"
                Layout.fillWidth: true
                internalName: "satFat"
                suffix: "%"

                max: 100 - monoFat.value - polyFat.value - transFat.value

                Layout.row: 0
            }

            IntGoalImpl {
                id: monoFat

                isRootItem: false

                name: "Monounsaturated Fat"
                Layout.fillWidth: true
                internalName: "monoFat"
                suffix: "%"

                max: 100 - satFat.value - polyFat.value - transFat.value

                Layout.row: 1
            }

            IntGoalImpl {
                id: polyFat

                isRootItem: false

                name: "Polyunsaturated Fat"
                Layout.fillWidth: true
                internalName: "polyFat"
                suffix: "%"

                max: 100 - satFat.value - monoFat.value - transFat.value
            }

            IntGoalImpl {
                id: transFat

                isRootItem: false

                name: "Trans Fat"
                Layout.fillWidth: true
                internalName: "transFat"
                suffix: "%"

                max: 100 - satFat.value - polyFat.value - monoFat.value
            }
        }

        IntGoalImpl {
            id: protein

            isRootItem: true

            name: "Protein"
            Layout.fillWidth: true
            internalName: "protein"
            suffix: "%"

            max: 100 - carbs.value - fat.value
        }
    }
}
