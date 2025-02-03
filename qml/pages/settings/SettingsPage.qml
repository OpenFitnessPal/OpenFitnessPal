import QtQuick
import QtQuick.Controls
import QtQuick.Layouts 6.6

import OpenFitnessPal

Rectangle {
    property date currentDate

    id: settings

    color: Constants.bg

    function back() {
        if (stack.depth > 1) {
            stack.pop()
            return true
        }

        return false
    }

    BetterStackView {
        id: stack
        initialItem: indexPage

        anchors {
            top: parent.top
            bottom: parent.bottom
            left: parent.left
            right: parent.right

            topMargin: 10 * Constants.scalar
        }

        InitialPage {
            id: indexPage

            onMeals: stack.push(meals)
            onGoals: stack.push(goals)
            onSearch: stack.push(search)
        }

        GoalsTab {
            visible: false
            id: goals

            currentDate: settings.currentDate

            onMacros: {
                macros.recalc()
                stack.push(macros)
            }
            onMicros: stack.push(micros)
        }

        MacrosPage {
            visible: false
            id: macros
        }

        MicrosPage {
            visible: false
            id: micros
        }

        SearchTab {
            visible: false
            id: search
        }

        MealsTab {
            visible: false
            id: meals
        }
    }
}
