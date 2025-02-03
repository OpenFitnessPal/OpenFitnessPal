import QtQuick
import QtQuick.Controls

import OpenFitnessPal

BaseSettingsTab {
    signal finished

    id: cardioEdit

    title: "Edit Cardio"

    property var bindedCardio: ({
                                    "name": "",
                                    "cals": 0,
                                    "time": 0
                                })

    UnlabeledTextField {
        id: name

        bindTarget: bindedCardio
        bindedProperty: "name"

        font.pixelSize: 22 * Constants.scalar
        font.bold: true

        background: Item {}

        anchors {
            top: nav.bottom
            left: parent.left
            right: parent.right

            topMargin: 10 * Constants.scalar
        }
    }

    SmallNumberField {
        id: min
        label: "min"
        attentive: false

        bindTarget: bindedCardio
        bindedProperty: "time"

        implicitWidth: 100 * Constants.scalar

        anchors {
            top: name.bottom
            left: parent.left

            leftMargin: 25 * Constants.scalar

            topMargin: 10 * Constants.scalar
        }
    }

    SmallNumberField {
        label: "kcal"
        attentive: false

        bindTarget: bindedCardio
        bindedProperty: "cals"

        implicitWidth: 100 * Constants.scalar

        anchors {
            top: name.bottom
            left: min.right

            leftMargin: 10 * Constants.scalar

            topMargin: 10 * Constants.scalar
        }
    }
}
