import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

Rectangle {
    signal add
    signal edit(var serving)

    id: mealLog

    color: Constants.sub

    height: 62 * Constants.scalar + (listView.count * (65 * Constants.scalar + listView.spacing))

    property int mealNumber: 0

    property string mealName

    function addFood(serving) {
        fm.add(serving)
        fm.cache(serving.item)
    }

    FoodModel {
        id: fm
        meal: mealNumber
        date: dateManager.date

        onDataChanged: {
            save()
            nutritionManager.updateNutrients()
        }
        Component.onCompleted: load()
    }

    ColumnLayout {
        spacing: 3

        anchors {
            top: parent.top
            left: parent.left
            right: parent.right

            margins: 8 * Constants.scalar
        }

        RowLayout {
            id: header

            implicitHeight: 60 * Constants.scalar

            Layout.fillWidth: true

            Text {
                Layout.fillWidth: true

                text: mealName
                color: Constants.text

                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 22 * Constants.scalar
                font.bold: true
            }

            NavButton {
                label: "Add"
                onClicked: mealLog.add()
            }
        }

        Rectangle {
            color: "gray"

            implicitHeight: 1
            Layout.fillWidth: true
        }

        FoodView {
            id: listView
            foods: fm

            onEdit: serving => mealLog.edit(serving)
        }
    }
}
