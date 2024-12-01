import QtQuick 2.15
import QtQuick.Controls 2.15

MealNameSettingForm {
    mealName.onEditingFinished: {
        settings.set("meal" + mealNumber + "Name", mealName.text)
        mealNamesChanged()
    }

    Component.onCompleted: {
        let name = settings.get("meal" + mealNumber + "Name")
        if (typeof name === "undefined") {
            name = defaultName

            settings.set("meal" + mealNumber + "Name", name)
            mealNamesChanged()
        }
        mealName.text = name;
    }

}
