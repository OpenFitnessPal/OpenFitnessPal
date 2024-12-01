import QtQuick 2.15

NutritionInfoForm {
    function reloadData(date) {
        let n = nutritionManager.getDailyNutrients(date)

        cal.reloadData(n.calories, 2500)
        carbs.reloadData(n.carbs, 35)
        fiber.reloadData(n.fiber, 20)
        sugar.reloadData(n.sugar, 120)
        fat.reloadData(n.fat, 35)
        sat.reloadData(n.satFat, 65)
        mono.reloadData(n.monoFat, 35)
        poly.reloadData(n.polyFat, 0)
        trans.reloadData(n.transFat, 0)
        protein.reloadData(n.protein, 30)
        cholesterol.reloadData(n.cholesterol, 600)
        sodium.reloadData(n.sodium, 6000)
        potassium.reloadData(n.potassium, 4000)
        vitaminA.reloadData(n.vitaminA, 100)
        vitaminC.reloadData(n.vitaminC, 100)
        calcium.reloadData(n.calcium, 100)
        iron.reloadData(n.iron, 100)
    }

    header.onRemoveRequested: closeOut()
}
