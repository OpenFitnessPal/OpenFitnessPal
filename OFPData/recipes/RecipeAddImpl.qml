import QtQuick 2.15

import OFPNative

RecipeAddForm {
    width: parent.width
    height: parent.height

    signal ready(var servings)

    property var recipe

    recipeName.text: recipe.name
    // servings.value: recipe.servings * 100

    servings.onValueChanged: resetNutrients()

    function reloadData() {
        servings.value = recipe.servings * 100
        resetNutrients()
    }

    // calories.text: Math.round(recipe.nutrients().calories * 10 * (servings.realValue / recipe.servings)) / 10.
    // carbs.text: Math.round(recipe.nutrients().carbs * 10 * (servings.realValue / recipe.servings)) / 10.
    // fat.text: Math.round(recipe.nutrients().fat * 10 * (servings.realValue / recipe.servings)) / 10.
    // protein.text: Math.round(recipe.nutrients().protein * 10 * (servings.realValue / recipe.servings)) / 10.

    function resetNutrients() {
        calories.text = Math.round(recipe.nutrients().calories * 10 * (servings.value / 100.0 / recipe.servings)) / 10.
        carbs.text = Math.round(recipe.nutrients().carbs * 10 * (servings.value / 100.0 / recipe.servings)) / 10.
        fat.text = Math.round(recipe.nutrients().fat * 10 * (servings.value / 100.0 / recipe.servings)) / 10.
        protein.text = Math.round(recipe.nutrients().protein * 10 * (servings.value / 100.0 / recipe.servings)) / 10.
    }
}
