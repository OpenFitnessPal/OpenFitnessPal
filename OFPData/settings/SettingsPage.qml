import QtQuick

SettingsPageForm {
    signal mealNamesChanged

    meal1Name.onEditingFinished: {
        settings.set("meal1Name", meal1Name.text)
        mealNamesChanged()
    }

    meal2Name.onEditingFinished: {
        settings.set("meal2Name", meal2Name.text)
        mealNamesChanged()
    }

    meal3Name.onEditingFinished: {
        settings.set("meal3Name", meal3Name.text)
        mealNamesChanged()
    }

    meal4Name.onEditingFinished: {
        settings.set("meal4Name", meal4Name.text)
        mealNamesChanged()
    }

    meal5Name.onEditingFinished: {
        settings.set("meal5Name", meal5Name.text)
        mealNamesChanged()
    }

    Component.onCompleted: {
        let reload = false

        let name1 = settings.get("meal1Name")
        if (typeof name1 === "undefined") {
            name1 = "Breakfast"
            settings.set("meal1Name", name1)
            reload = true
        }
        meal1Name.text = name1;

        let name2 = settings.get("meal2Name")
        if (typeof name2 === "undefined") {
            name2 = "Lunch"
            settings.set("meal2Name", name2)
            reload = true
        }
        meal2Name.text = name2;

        let name3 = settings.get("meal3Name")
        if (typeof name3 === "undefined") {
            name3 = "Dinner"
            settings.set("meal3Name", name3)
            reload = true
        }
        meal3Name.text = name3;

        let name4 = settings.get("meal4Name")
        if (typeof name4 === "undefined") {
            name4 = "Preworkout"
            settings.set("meal4Name", name4)
            reload = true
        }
        meal4Name.text = name4;

        let name5 = settings.get("meal5Name")
        if (typeof name5 === "undefined") {
            name5 = "Postworkout"
            settings.set("meal5Name", name5)
            reload = true
        }
        meal5Name.text = name5;

        if (reload) mealNamesChanged()
    }

}
