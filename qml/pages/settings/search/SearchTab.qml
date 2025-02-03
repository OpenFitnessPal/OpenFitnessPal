import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

BaseSettingsTab {
    id: search

    title: "Search Settings"

    ColumnLayout {
        height: 100 * Constants.scalar

        anchors {
            top: nav.bottom
            left: parent.left
            right: parent.right

            margins: 8 * Constants.scalar
        }

        LabeledCheckbox {
            label: "Prefer Generics?"

            bindTarget: searchSettings
            bindedProperty: "preferGenerics"
        }

        LabeledNumberField {
            Layout.fillWidth: true

            label: "Results"
            suffix: ""

            bindTarget: searchSettings
            bindedProperty: "results"
        }
    }
}
