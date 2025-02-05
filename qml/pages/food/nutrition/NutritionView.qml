import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

BaseSettingsTab {
    property nutrientUnion nutrients

    id: nutritionView

    title: "Nutrition"

    RowLayout {
        id: header
        anchors {
            top: nav.bottom
            left: parent.left
            right: parent.right
        }

        uniformCellSizes: true

        implicitHeight: 40 * Constants.scalar

        Repeater {
            model: 3

            Item {
                Layout.fillWidth: true
            }
        }

        Repeater {
            model: ["Total", "Goal", "Left"]

            Text {
                text: modelData
                color: Constants.text

                font.pixelSize: 14 * Constants.scalar

                Layout.fillWidth: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignBottom
            }
        }
    }

    ListView {
        id: listView
        model: nutrientsModel

        anchors {
            top: header.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom

            margins: 8 * Constants.scalar
        }

        clip: true
        boundsBehavior: Flickable.StopAtBounds

        delegate: NutrientView {
            clip: true
            width: listView.width
        }
    }
}
