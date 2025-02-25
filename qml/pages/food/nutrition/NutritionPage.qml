import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

BaseSettingsTab {
    signal updateNutrients

    property nutrientUnion nutrients
    property list<nutrientUnion> dailyNutrients

    property date currentDate

    id: nutritionPage

    title: "Nutrition"

    // get week/month/etc nutrients
    NutritionManager {
        id: nm

        date: currentDate
    }

    property alias daysBack: select.daysBack

    onUpdateNutrients: {
        nutrients = nm.load(daysBack)
        dailyNutrients = nm.list(daysBack)
    }
    onDaysBackChanged: updateNutrients()

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

            nutrients: nutritionPage.nutrients
        }

        MacroView {
            id: macroView

            nutrients: nutritionPage.nutrients
            dailyNutrients: nutritionPage.dailyNutrients
            daysBack: nutritionPage.daysBack
            currentDayOfWeek: currentDate.getUTCDay()
        }
    }
}
