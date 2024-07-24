import QtQuick 2.15

import OFPTest

RecipesPageForm {
    id: impl
    // width: parent.width

    // Recipe {
    //     id: blankRecipe
    // }

    add.onClicked: {
        recipeDialog.recipeEdit.recipe = blankRecipe
        recipeDialog.open()
        recipeDialog.recipeEdit.ready.connect(addRecipe)
    }

    RecipeListModel {
        id: rlm
        meal: 0
    }

    Component.onCompleted: {
        rlm.loadData()
    }

    listView.model: rlm
    listView.delegate: RecipeInfoImpl {
        function editEntry(recipe) {
            model.recipe = recipe

            rlm.saveData()
            reloadData()

            recipeDialog.recipeEdit.ready.disconnect(editEntry)
        }

        mouse.onClicked: {
            recipeDialog.recipeEdit.recipe = model.recipe

            recipeDialog.recipeEdit.loadData()
            recipeDialog.open()

            recipeDialog.recipeEdit.ready.connect(editEntry)
        }

        onDeleteRecipe: {
            rlm.removeRow(recipeID)
            rlm.saveData()
        }

        Component.onCompleted: reloadData()

        remove.visible: true
    }
    listView.clip: true

    function addRecipe(recipe) {
        search.food.searchReady.disconnect(addRecipe)
        rlm.add(recipe);

        rlm.saveData()
    }
}
