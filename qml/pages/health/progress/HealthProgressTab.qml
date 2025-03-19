import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

BaseTab {
    id: progressTab

    title: "Health Progress"

    property list<healthMarker> currentList

    HealthMarkerProgressManager {
        id: pm

        date: dateManager.date
    }
}
