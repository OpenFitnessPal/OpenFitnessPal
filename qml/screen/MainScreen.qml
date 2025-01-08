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
            picker.currentDate = currentDate
            picker.open()
        }
    }

    DatePicker {
        id: picker

        onAccepted: {
            dateSelect.currentDate = currentDate
        }
    }

    SwipeView {
        id: swipe

        currentIndex: tabBar.currentIndex

        function back() {
            // if false, there was no operation to be done
            if (!currentItem.back()) {
                // TODO: make it go to previous page
                // if no previous page, exit
                console.log("UNIMPLEMENTED")

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
            model: ["Overview", "Exercise", "Food", "More"]

            IconTabButton {
                text: modelData
            }
        }
    }
}
