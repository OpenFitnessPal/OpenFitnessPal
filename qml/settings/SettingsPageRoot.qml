import QtQuick 2.15

SettingsPageRootForm {
    id: impl

    signal reloadCache
    signal reloadData

    signal mealNamesChanged

    search.onGoBack: swipe.setCurrentIndex(0)
    main.onGoToSearchSettings: {
        swipe.setCurrentIndex(1)
    }

    main.onReloadCache: impl.reloadCache()
    main.onReloadData: impl.reloadData()
    main.onMealNamesChanged: impl.mealNamesChanged()
}
