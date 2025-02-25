import QtQuick
import QtQuick.Controls
import QtQuick.Layouts 6.6

import OpenFitnessPal

Rectangle {
    property date currentDate

    function back() {}

    id: overview

    color: Constants.bg

    ScrollView {
        width: parent.width
        height: parent.height - 8 * Constants.scalar

        y: 8 * Constants.scalar

        contentWidth: parent.width - effectiveScrollBarWidth

        id: scroll

        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

        ColumnLayout {
            anchors {
                fill: parent
            }
        }
    }
}
