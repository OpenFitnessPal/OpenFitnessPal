import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

BaseSettingsTab {
    signal updateNutrients

    property nutrientUnion nutrients
    property date currentDate

    id: nutritionPage

    title: "Nutrition"

    // get week/month/etc nutrients
    NutritionManager {
        id: nm

        date: currentDate
    }

    property int daysBack: 1

    onUpdateNutrients: nutrients = nm.load(daysBack)
    onDaysBackChanged: nutrients = nm.load(daysBack)

    DaysBackDialog {
        id: backDialog

        onSelect: (selection, label) => {
                      viewLabel.text = label
                      nutritionView.daysBack = selection
                  }
    }

    Rectangle {
        id: combo

        color: Constants.sub

        anchors {
            top: nav.bottom
            left: parent.left
            right: parent.right

            topMargin: 5 * Constants.scalar
        }

        implicitHeight: 35 * Constants.scalar

        MouseArea {
            anchors.fill: parent
            onClicked: backDialog.open()

            RowLayout {
                anchors {
                    fill: parent

                    rightMargin: 10 * Constants.scalar
                }

                Text {
                    id: viewLabel

                    Layout.fillWidth: true

                    color: Constants.text

                    text: "Today"

                    font.pixelSize: 14 * Constants.scalar

                    horizontalAlignment: Text.AlignHCenter
                }
            }
        }
    }

    TabBar {
        id: tabBar

        currentIndex: swipe.currentIndex

        position: TabBar.Header
        anchors {
            top: combo.bottom
            left: parent.left
            right: parent.right

            topMargin: 5 * Constants.scalar
        }

        implicitHeight: 40 * Constants.scalar

        background: Rectangle {
            color: Constants.sub
        }

        Repeater {
            model: ["Nutrients", "Macros"]

            TabButton {
                text: modelData

                font.pixelSize: 16 * Constants.scalar
            }
        }
    }

    SwipeView {
        id: swipe

        anchors {
            top: tabBar.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

        interactive: false

        currentIndex: tabBar.currentIndex

        NutritionView {
            nutrients: nutritionPage.nutrients
            onNutrientsChanged: console.log(nutrients)
        }
    }
}
