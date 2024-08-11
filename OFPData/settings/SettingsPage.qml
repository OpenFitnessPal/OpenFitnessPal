import QtQuick

SettingsPageForm {
    id: impl
    signal mealNamesChanged

    signal reloadCache
    signal reloadData

    dataDir.onReloadData: impl.reloadData()
    cacheDir.onReloadData: impl.reloadCache()

    meal1.onMealNamesChanged: impl.mealNamesChanged()
    meal2.onMealNamesChanged: impl.mealNamesChanged()
    meal3.onMealNamesChanged: impl.mealNamesChanged()
    meal4.onMealNamesChanged: impl.mealNamesChanged()
    meal5.onMealNamesChanged: impl.mealNamesChanged()

}
