import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

BaseTab {
    id: nutritionPage

    title: "Nutrition"

    property bool weekView: select.daysBack > 1

    onNavClicked: tabBar.currentIndex = 0

    DaysBackDialog {
        id: backDialog

        onSelect: (selection, label) => {
                      select.text = label
                      select.daysBack = selection
                  }
    }

    DaysBackButton {
        id: select

        anchors {
            top: nav.bottom
            left: parent.left
            right: parent.right

            topMargin: 5 * Constants.scalar
        }
    }

    TabBar {
        id: tabBar

        currentIndex: swipe.currentIndex

        position: TabBar.Header
        anchors {
            top: select.bottom
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
            id: nutritionView

            weekView: nutritionPage.weekView
        }

        MacroView {
            id: macroView

            weekView: nutritionPage.weekView
        }
    }
}
