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

    property date currentDate: new Date()

    property int mealNumber: 0

    property string mealName

    property alias calories: fm.calories
    property alias nutrients: fm.nutrients

    function addFood(serving) {
        fm.add(serving)
        fm.cache(serving.item)
    }

    FoodModel {
        id: fm
        meal: mealNumber
        date: mealLog.currentDate

        onDataChanged: save()
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

        ListView {
            id: listView

            model: fm
            spacing: 5 * Constants.scalar

            Layout.fillHeight: true
            Layout.fillWidth: true

            height: (count * (65 * Constants.scalar + spacing))
            contentHeight: height

            interactive: false
            clip: false

            function fixHeight() {
                height = (count * (65 * Constants.scalar
                                   + spacing)) // needs to be force-set for some reason
            }

            onHeightChanged: fixHeight()
            onCountChanged: fixHeight()

            delegate: FoodPreview {
                width: listView.width
                height: 65 * Constants.scalar
                onDeleteRequested: fm.remove(idx)

                onClicked: mealLog.edit(model)
            }
        }
    }
}
