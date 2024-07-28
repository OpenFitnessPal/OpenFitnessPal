import QtQuick 2.15

NutritionGoalForm {
    width: parent.width
    function reloadData(newValue) {
        let goalValue = goalManager.getValue(internalName)

        if (isPercent) {
            let div = isFat ? 9. : 4.
            let calories = goalManager.getValue("calories")

            goalValue = goalValue / 100. * calories / div
        }

        let left = goalValue - newValue

        total.text = Math.round(newValue * 10.) / 10.
        amountLeft.text = Math.round(left * 10.) / 10. + suffix
        goal.text = Math.round(goalValue * 10.) / 10.

        progressBar.value = newValue / goalValue
    }
}
