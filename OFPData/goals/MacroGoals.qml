import QtQuick 2.15

MacroGoalsForm {
    id: impl
    height: 420

    property bool startup: true

    function setMacros(newCarbs, newFat, newProtein) {

        console.log("Carbs: " + newCarbs + " Fat: " + newFat + " Carbs: " + newProtein)

        // carbs.value = newCarbs
        // fat.value = newFat
        // protein.value = newProtein

        carbs.spinBox.value = newCarbs
        fat.spinBox.value = newFat
        protein.spinBox.value = newProtein
    }

    function checkMacrosValid() {
        if (startup) {
            carbs.value = goalManager.getValue("carbs")
            fat.value = goalManager.getValue("fat")
            protein.value = goalManager.getValue("protein")
        }

        let valid = (carbs.value + protein.value + fat.value) == 100

        carbs.isValid = valid
        fat.isValid = valid
        protein.isValid = valid

        carbs.max = 100 - fat.value - protein.value
        fat.max = 100 - carbs.value - protein.value
        protein.max = 100 - fat.value - carbs.value

        if (valid && !startup) {
            goalManager.setValue("carbs", carbs.value)
            goalManager.setValue("fat", fat.value)
            goalManager.setValue("protein", protein.value)
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
