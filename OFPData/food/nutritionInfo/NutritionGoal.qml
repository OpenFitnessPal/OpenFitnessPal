import QtQuick 2.15

NutritionGoalForm {
    function reloadData(newValue) {
        let goalValue = goalManager.getValue(internalName)

        let left = goalValue - newValue

        total.text = newValue
        amountLeft.text = left
        goalValue.text = goalValue + suffix

        progressBar.value = newValue / goalValue
    }
}
