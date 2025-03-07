import QtQuick
import QtQuick.Controls
import QtQuick.Layouts 6.6

import OpenFitnessPal

Rectangle {
    id: screen

    color: Constants.bg

    function back() {
        return swipe.back()
    }

    DateSelector {
        id: dateSelect

        anchors {
            top: parent.top
            left: parent.left
            right: parent.right

            margins: 4
        }

        onPickDate: {
            picker.open()
        }
    }

    DatePicker {
        id: picker
    }

    SwipeView {
        id: swipe

        currentIndex: tabBar.currentIndex

        function back() {
            // if false, there was no operation to be done
            if (!currentItem.back()) {
                // return false to NOT accept the close event, true to accept
                return true
            }

            return false
        }

        anchors {
            top: dateSelect.bottom
            left: parent.left
            right: parent.right
            bottom: tabBar.top
        }

        OverviewPage {
            id: overview
        }

        ExercisePage {
            id: exercise
        }

        FoodPage {
            id: food

            exerciseCalories: exercise.calories
        }

        RecipePage {
            id: recipe
        }

        SettingsPage {
            id: settings
        }
    }

    TabBar {
        id: tabBar

        currentIndex: swipe.currentIndex

        anchors {
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }

        Repeater {
            model: ["Overview", "Exercise", "Food", "Recipes", "More"]

            IconTabButton {
                text: modelData
            }
        }
    }
}
