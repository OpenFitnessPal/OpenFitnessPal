import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

RowLayout {
    implicitHeight: 40 * Constants.scalar
    spacing: 10 * Constants.scalar

    NavButton {
        label: "Delete"
        onClicked: sets.remove(idx)

        implicitWidth: 40 * Constants.scalar
        implicitHeight: 40 * Constants.scalar
    }

    SmallNumberField {
        implicitWidth: 100 * Constants.scalar
        id: weightEdit

        label: "lbs"

        bindTarget: model
        bindedProperty: "weight"

        attentive: false
    }

    SmallNumberField {
        implicitWidth: 100 * Constants.scalar
        id: repsEdit

        label: "reps"

        bindTarget: model
        bindedProperty: "reps"

        attentive: false
    }
}
