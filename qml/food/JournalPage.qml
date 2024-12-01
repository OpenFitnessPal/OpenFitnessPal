import QtQuick 2.15

JournalPageForm {
    function reloadMealNames() {
        mealLog1.reloadMealName()
        mealLog2.reloadMealName()
        mealLog3.reloadMealName()
        mealLog4.reloadMealName()
        mealLog5.reloadMealName()
    }

    mealLog1.mealNumber: 1
    mealLog2.mealNumber: 2
    mealLog3.mealNumber: 3
    mealLog4.mealNumber: 4
    mealLog5.mealNumber: 5

    mealLog1.onNutritionUpdated: calPreview.reloadData(currentDate)
    mealLog2.onNutritionUpdated: calPreview.reloadData(currentDate)
    mealLog3.onNutritionUpdated: calPreview.reloadData(currentDate)
    mealLog4.onNutritionUpdated: calPreview.reloadData(currentDate)
    mealLog5.onNutritionUpdated: calPreview.reloadData(currentDate)

    function reloadData(currentDate) {
        mealLog1.currentDate = currentDate
        mealLog1.reloadData()

        mealLog2.currentDate = currentDate
        mealLog2.reloadData()

        mealLog3.currentDate = currentDate
        mealLog3.reloadData()

        mealLog4.currentDate = currentDate
        mealLog4.reloadData()

        mealLog5.currentDate = currentDate
        mealLog5.reloadData()

        calPreview.reloadData(currentDate)
    }

    calPreview.onClicked: nutritionInfoRequested()
    Component.onCompleted: {
        reloadMealNames()
        calPreview.reloadData(currentDate)
    }
}
