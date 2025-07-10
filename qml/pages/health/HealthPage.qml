import QtQuick

import OpenFitnessPal

Rectangle {
    id: settings

    color: Constants.bg

    function back() {
        if (stack.depth > 1) {
            stack.pop()
            return true
        }

        return false
    }

    BetterStackView {
        id: stack
        initialItem: indexPage

        anchors {
            top: parent.top
            bottom: parent.bottom
            left: parent.left
            right: parent.right

            topMargin: 10 * Constants.scalar
        }

        HealthIndexPage {
            id: indexPage

            onMarkers: stack.push(markersTab)
            onSymptoms: stack.push(symptomsTab)
            onProgress: stack.push(progressTab)
        }

        MarkersTab {
            id: markersTab
            visible: false
        }

        SymptomsTab {
            id: symptomsTab
            visible: false
        }

        HealthProgressTab {
            id: progressTab
            visible: false
        }
    }
}
