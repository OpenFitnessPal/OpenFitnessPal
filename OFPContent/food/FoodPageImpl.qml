import QtQuick 2.15

FoodPageForm {
    id: impl
    mealLog1.mealName.text: settings.meal1Name
    mealLog2.mealName.text: settings.meal2Name
    mealLog3.mealName.text: settings.meal3Name
    mealLog4.mealName.text: settings.meal4Name
    mealLog5.mealName.text: settings.meal5Name

    mealLog1.mealNumber: 1
    mealLog2.mealNumber: 2
    mealLog3.mealNumber: 3
    mealLog4.mealNumber: 4
    mealLog5.mealNumber: 5

    function reloadData() {
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
    }
}
