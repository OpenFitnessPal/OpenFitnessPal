import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

TextButton {
    id: select

    onClicked: backDialog.open()

    name: "Today"
    fontSize: 14

    implicitHeight: 35 * Constants.scalar

    property alias text: select.name
    property int daysBack: 1
}
