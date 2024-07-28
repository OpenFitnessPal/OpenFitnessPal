import QtQuick 2.15

NutritionInfoForm {
    function reloadData(date) {
        let n = nutritionManager.getDailyNutrients(date)

        cal.reloadData(n.calories)
        carbs.reloadData(n.carbs)
        fiber.reloadData(n.fiber)
        sugar.reloadData(n.sugar)
        fat.reloadData(n.fat)
        sat.reloadData(n.satFat)
        mono.reloadData(n.monoFat)
        poly.reloadData(n.polyFat)
        trans.reloadData(n.transFat)
        protein.reloadData(n.protein)
        cholesterol.reloadData(n.cholesterol)
        sodium.reloadData(n.sodium)
        potassium.reloadData(n.potassium)
        vitaminA.reloadData(n.vitaminA)
        vitaminC.reloadData(n.vitaminC)
        calcium.reloadData(n.calcium)
        iron.reloadData(n.iron)
    }
}
