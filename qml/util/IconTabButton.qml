import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

TabButton {
    id: button

    height: 75 * Constants.scalar

    contentItem: ColumnLayout {
        Button {
            Layout.maximumHeight: 50 * Constants.scalar
            Layout.maximumWidth: 50 * Constants.scalar

            id: image
            icon.source: "qrc:/" + button.text
            icon.width: 20 * Constants.scalar
            icon.height: 20 * Constants.scalar
            icon.color: index === tabBar.currentIndex ? Constants.text : "gray"

            background: Item {}

            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

            onClicked: button.click()
        }

        Label {
            font.pixelSize: Math.round(12 * Constants.scalar)
            text: button.text

            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

            color: index === tabBar.currentIndex ? Constants.text : "gray"
        }
    }
}
