import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

BaseTab {
    id: markersTab

    title: "Symptom Logs"

    ListView {
        model: SymptomLogModel {
            id: slm

            date: dateManager.date
        }

        clip: true

        anchors {
            top: nav.bottom
            bottom: button.top

            left: parent.left
            right: parent.right

            margins: 10 * Constants.scalar
        }

        spacing: 10 * Constants.scalar

        id: listView

        delegate: SymptomLog {
            width: listView.width

            onDeleteRequested: slm.remove(idx)
        }

        focusPolicy: Qt.StrongFocus
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

        text: "Log Symptom"
        onClicked: slm.add()

        background: Rectangle {
            color: button.pressed ? Constants.accentPressed : Constants.accent
            radius: 5 * Constants.scalar
        }
    }
}
