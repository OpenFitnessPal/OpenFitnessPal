import QtQuick

SettingsPageForm {
    id: impl

    signal goToSearchSettings

    signal reloadCache
    signal reloadData

    dataDir.onReloadData: impl.reloadData()
    cacheDir.onReloadData: impl.reloadCache()

    repeater.delegate: MealNameSetting {
        required property int index
        required property string modelData

        mealNumber: index + 1
        defaultName: modelData

        onMealNamesChanged: impl.mealNamesChanged()
    }

    searchSettings.onClicked: {
        goToSearchSettings()
    }
}
