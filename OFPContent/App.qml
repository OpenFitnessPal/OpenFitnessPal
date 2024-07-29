import QtQuick
import QtQuick.Controls

import OFPData

Window {
    id: window
    width: Constants.width
    height: Constants.height

    visible: true

    function newDate(date) {
        exercisesPage.currentDate = date
        foodPage.currentDate = date

        exercisesPage.reloadData()
        foodPage.reloadData()
    }

    Dialog {
        id: search
        width: window.width
        height: window.height

        property alias food: food

        FoodSearchImpl {
            id: food
            width: parent.width
            height: parent.height

            back.onClicked: search.reject()
        }
    }

    Dialog {
        id: foodEdit
        width: window.width
        height: window.height

        property alias edit: edit

        FoodServingEditImpl {
            id: edit
            width: parent.width
            height: parent.height

            back.onClicked: foodEdit.reject()

            submit.onClicked: {
                foodEdit.accept()

                ready([foodServing])
            }
        }
    }

    Dialog {
        id: recipeDialog
        width: window.width
        height: window.height

        property alias recipeEdit: recipeEdit

        RecipeEditImpl {
            id: recipeEdit
            width: parent.width
            height: parent.height

            back.onClicked: recipeDialog.reject()

            submit.onClicked: {
                recipeDialog.accept()
                recipe.name = recipeName.text

                ready(recipe)
            }
        }
    }

    Dialog {
        id: recipeAdd
        width: window.width
        height: window.height

        property alias add: add

        RecipeAddImpl {
            id: add
            width: parent.width
            height: parent.height

            back.onClicked: recipeAdd.reject()

            submit.onClicked: {
                recipeAdd.accept();

                ready(recipe.asServings(servings.value / 100.0));
            }
        }
    }

    SwipeView {
        id: swipeView
        objectName: "swipeView"
        anchors.bottom: tabBar.bottom
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.top: dateSelect.bottom
        anchors.left: parent.left
        currentIndex: tabBar.currentIndex

        SettingsPage {
        }

        ExercisePageImpl {
            id: exercisesPage

            Component.onCompleted: {
                currentDate = new Date()
                reloadData()
            }
        }

        FoodPageImpl {
            id: foodPage
            Component.onCompleted: {
                currentDate = new Date()
                reloadData()
            }
        }

        RecipesPageImpl {
        }

        GoalsPageImpl {
        }
    }

    TabBar {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 0
        anchors.rightMargin: 0
        layer.enabled: false
        transformOrigin: Item.Center

        id: tabBar
        y: parent.height - height
        position: TabBar.Footer
        currentIndex: swipeView.currentIndex

        TabButton {
            text: qsTr("Settings")
        }
        TabButton {
            text: qsTr("Exercise")
        }
        TabButton {
            text: qsTr("Food")
        }
        TabButton {
            text: qsTr("Recipes")
        }
        TabButton {
            text: qsTr("Goals")
        }
    }

    DateSelect {
        id: dateSelect
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.horizontalCenter: parent.horizontalCenter

        onDateChanged: (date) => newDate(date)
    }
}
