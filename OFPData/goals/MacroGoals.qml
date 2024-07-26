import QtQuick 2.15

MacroGoalsForm {
    id: impl
    height: 420

    function checkMacrosValid() {
        let valid = (carbs.value + protein.value + fat.value) == 100
        console.log((carbs.value + protein.value + fat.value))

        carbs.isValid = valid;
        fat.isValid = valid;
        protein.isValid = valid;

        console.log(valid)
    }

    carbs.onGoalValueChanged: checkMacrosValid()
    fat.onGoalValueChanged: checkMacrosValid()
    protein.onGoalValueChanged: checkMacrosValid()
}
