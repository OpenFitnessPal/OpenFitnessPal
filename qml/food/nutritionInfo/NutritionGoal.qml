import QtQuick 2.15

NutritionGoalForm {
    width: parent.width
    function reloadData(newValue, defaultValue) {
        let goalValue = goalManager.get(internalName, defaultValue)

        // TODO: properly sort things for the submacros
        if (isPercent) {
            let div = isFat ? 9. : 4.
            let calories = goalManager.get("calories", 2500)

            goalValue = goalValue / 100. * calories / div
        }

        let left = goalValue - newValue

        total.text = Math.round(newValue * 10.) / 10.
        amountLeft.text = Math.round(left * 10.) / 10. + suffix
        goal.text = Math.round(goalValue * 10.) / 10.

        progressBar.value = newValue / goalValue
    }
}
