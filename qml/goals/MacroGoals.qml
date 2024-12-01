import QtQuick 2.15

MacroGoalsForm {
    height: 460

    property bool startup: true

    function setMacros(newCarbs, newFat, newProtein) {
        carbs.goalValueChanged.disconnect(checkMacrosValid)
        fat.goalValueChanged.disconnect(checkMacrosValid)
        protein.goalValueChanged.disconnect(checkMacrosValid)

        carbs.max = 100
        fat.max = 100
        protein.max = 100

        carbs.setValue(newCarbs)
        fat.setValue(newFat)
        protein.setValue(newProtein)

        checkMacrosValid()

        carbs.goalValueChanged.connect(checkMacrosValid)
        fat.goalValueChanged.connect(checkMacrosValid)
        protein.goalValueChanged.connect(checkMacrosValid)
    }

    function checkMacrosValid() {
        if (startup) {
            carbs.value = goalManager.get("carbs", 35)
            fat.value = goalManager.get("fat", 35)
            protein.value = goalManager.get("protein", 30)
            startup = false
        }

        let valid = (carbs.value + protein.value + fat.value) == 100

        carbs.isValid = valid
        fat.isValid = valid
        protein.isValid = valid

        carbs.max = 100 - fat.value - protein.value
        fat.max = 100 - carbs.value - protein.value
        protein.max = 100 - fat.value - carbs.value

        if (valid && !startup) {
            goalManager.set("carbs", carbs.value)
            goalManager.set("fat", fat.value)
            goalManager.set("protein", protein.value)
        }

        startup = false
    }

    carbs.onGoalValueChanged: checkMacrosValid()
    fat.onGoalValueChanged: checkMacrosValid()
    protein.onGoalValueChanged: checkMacrosValid()

    function checkCarbsValid() {
        let valid = (fiber.value + sugar.value) <= 100

        fiber.isValid = valid
        sugar.isValid = valid

        fiber.max = 100 - sugar.value
        sugar.max = 100 - fiber.value
    }

    fiber.onGoalValueChanged: checkCarbsValid()
    sugar.onGoalValueChanged: checkCarbsValid()

    function checkFatsValid() {
        let valid = (satFat.value + monoFat.value + polyFat.value + transFat.value) <= 100

        satFat.isValid = valid
        monoFat.isValid = valid
        polyFat.isValid = valid
        transFat.isValid = valid

        satFat.max = 100 - monoFat.value - polyFat.value - transFat.value
        monoFat.max = 100 - satFat.value - polyFat.value - transFat.value
        polyFat.max = 100 - monoFat.value - satFat.value - transFat.value
        transFat.max = 100 - monoFat.value - polyFat.value - satFat.value
    }

    satFat.onGoalValueChanged: checkFatsValid()
    monoFat.onGoalValueChanged: checkFatsValid()
    polyFat.onGoalValueChanged: checkFatsValid()
    transFat.onGoalValueChanged: checkFatsValid()

    Component.onCompleted: checkMacrosValid()
}
