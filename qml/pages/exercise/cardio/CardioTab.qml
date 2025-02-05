import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

BaseSettingsTab {
    property date currentDate

    id: cardioPage

    title: "Cardio"

    property alias calories: cm.calories

    signal editCardio(var cardio)

    CardioModel {
        date: cardioPage.currentDate

        id: cm
    }

    Component.onCompleted: cm.load()

    CardioPresetDialog {
        id: presets

        onAdd: name => cm.add(name)
    }

    ListView {
        id: listView

        clip: true

        anchors {
            top: nav.bottom
            bottom: button.top
            left: parent.left
            right: parent.right

            leftMargin: 10 * Constants.scalar
            rightMargin: 10 * Constants.scalar

            topMargin: 5 * Constants.scalar
        }

        spacing: 10 * Constants.scalar

        boundsBehavior: Flickable.StopAtBounds

        model: cm

        delegate: CardioPreview {
            width: listView.width

            onClicked: editCardio(model)
        }
    }

    Button {
        id: button
        font.pixelSize: 25 * Constants.scalar

        anchors {
            left: parent.left
            right: parent.right

            bottom: parent.bottom

            margins: 8 * Constants.scalar
        }

        text: "Add Cardio"
        onClicked: presets.open()

        background: Rectangle {
            color: button.pressed ? Constants.accentPressed : Constants.accent
            radius: 5 * Constants.scalar
        }
    }
}
