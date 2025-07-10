import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

BaseTab {
    id: exercisePage

    title: "Exercises"

    function add(exercises) {
        em.add(exercises)
    }

    Component.onCompleted: em.load()

    ExerciseModel {
        date: dateManager.date
        id: em
    }

    ExerciseList {
        model: em

        anchors {
            top: nav.bottom
            bottom: parent.bottom
            left: parent.left
            right: parent.right

            topMargin: 5 * Constants.scalar
        }
    }
}
