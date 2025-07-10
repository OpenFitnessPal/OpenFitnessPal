import QtQuick

import OpenFitnessPal

Rectangle {
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
            onDataButton: stack.push(data)
        }

        GoalsTab {
            visible: false
            id: goals

            onMacros: {
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

        DataTab {
            visible: false
            id: data
        }
    }
}
