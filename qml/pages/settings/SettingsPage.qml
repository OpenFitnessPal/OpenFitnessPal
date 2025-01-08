import QtQuick
import QtQuick.Controls
import QtQuick.Layouts 6.6

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

            topMargin: 10
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
