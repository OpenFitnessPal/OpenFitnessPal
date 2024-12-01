

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

    property alias sugar: sugar
    property alias fiber: fiber

    property alias satFat: satFat
    property alias monoFat: monoFat
    property alias polyFat: polyFat
    property alias transFat: transFat

    ColumnLayout {
        anchors.fill: parent

        anchors.leftMargin: 8
        anchors.rightMargin: 8
        anchors.topMargin: 8
        anchors.bottomMargin: 8

        IntGoal {
            id: carbs
            value: 40

            isRootItem: true

            name: "Carbohydrates"
            Layout.fillWidth: true
            internalName: "carbs"
            suffix: "%"
        }

        ColumnLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.leftMargin: 30

            IntGoal {
                id: fiber
                value: 10

                isRootItem: false

                name: "Fiber"
                Layout.fillWidth: true
                internalName: "fiber"
                suffix: "%"
            }

            IntGoal {
                id: sugar
                value: 20

                isRootItem: false

                name: "Sugar"
                Layout.fillWidth: true
                internalName: "sugar"
                suffix: "%"
            }
        }

        IntGoal {
            id: fat
            value: 30

            isRootItem: true

            name: "Fat"
            Layout.fillWidth: true
            internalName: "fat"
            suffix: "%"
        }

        ColumnLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.leftMargin: 30

            IntGoal {
                id: satFat
                value: 65

                isRootItem: false

                name: "Saturated Fat"
                Layout.fillWidth: true
                internalName: "sat"
                suffix: "%"

                Layout.row: 0
            }

            IntGoal {
                id: monoFat
                value: 30

                isRootItem: false

                name: "Monounsaturated Fat"
                Layout.fillWidth: true
                internalName: "mono"
                suffix: "%"

                Layout.row: 1
            }

            IntGoal {
                id: polyFat
                value: 5

                isRootItem: false

                name: "Polyunsaturated Fat"
                Layout.fillWidth: true
                internalName: "poly"
                suffix: "%"
            }

            IntGoal {
                id: transFat
                value: 0

                isRootItem: false

                name: "Trans Fat"
                Layout.fillWidth: true
                internalName: "trans"
                suffix: "%"
            }
        }

        IntGoal {
            id: protein
            value: 30

            isRootItem: true

            name: "Protein"
            Layout.fillWidth: true
            internalName: "protein"
            suffix: "%"
        }
    }
}
