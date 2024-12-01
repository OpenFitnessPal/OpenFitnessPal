import QtQuick 2.15

CaloriePreviewForm {
    function reloadData(currentDate) {
        let goalValue = goalManager.get("calories", 2500)
        let foodValue = nutritionManager.getDailyNutrients(currentDate).calories
        let remainingValue = goalValue - foodValue

        goal.text = Math.round(goalValue * 10.) / 10.
        food.text = Math.round(foodValue * 10.) / 10.
        remaining.text = Math.round(remainingValue * 10.) / 10.
    }

    mouse.onClicked: clicked()
}
