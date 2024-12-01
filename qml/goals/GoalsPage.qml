import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs

GoalsPageForm {
    MessageDialog {
        id: messageDialog
        title: "Recalculate Calorie/Macro Goals?"
        text: "Are you sure you want to overwrite target calorie/macro data?"

        visible: false

        buttons: MessageDialog.Yes | MessageDialog.No
    }

    function confirmedRecalc() {
        messageDialog.accepted.disconnect(confirmedRecalc)

        let weightMultiplier = 0.
        let carbsPercentage = 30.
        let fatPercentage = 35.
        let proteinPercentage = 35.

        let weightLbs = weight.value

        switch (goal.index) {
            // fast weight loss
        case 0:
            weightMultiplier = 12.
            carbsPercentage = 25.
            fatPercentage = 30.
            proteinPercentage = 45.
            break
            // slow weight loss
        case 1:
            weightMultiplier = 14.
            fatPercentage = 30.
            proteinPercentage = 40.
            break
            // maintain
        case 2:
            weightMultiplier = 15.
            break
            // slow weight gain
        case 3:
            weightMultiplier = 16.
            carbsPercentage = 35.
            fatPercentage = 30.
            proteinPercentage = 35.
            break
            // fast weight gain
        case 4:
            weightMultiplier = 18.
            carbsPercentage = 35.
            fatPercentage = 35.
            proteinPercentage = 30.
            break
        default:
            break
        }

        calories.spinBox.value = (weightLbs * weightMultiplier)
        calories.value = calories.spinBox.value

        let carbs = (carbsPercentage)
        let fat = (fatPercentage)
        let protein = (proteinPercentage)

        macros.setMacros(carbs, fat, protein)

        goalManager.set("goal", goal.index)
    }

    function recalcGoals() {
        messageDialog.accepted.connect(confirmedRecalc)
        messageDialog.open()
    }

    recalc.onClicked: recalcGoals()
    goal.onGoalChanged: recalcGoals()
    calories.onGoalValueChanged: {
        goalManager.set("calories", calories.value)
        changeNutrition()
    }
}
