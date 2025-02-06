import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

BaseSettingsTab {
    signal updateNutrients

    property date currentDate

    property nutrientUnion nutrients

    property int daysBack: 1

    // get week/month/etc nutrients
    NutritionManager {
        id: nm

        date: currentDate
    }

    onUpdateNutrients: nutrients = nm.load(daysBack)
    onDaysBackChanged: nutrients = nm.load(daysBack)

    DaysBackDialog {
        id: backDialog

        onSelect: (selection, label) => {
                      viewLabel.text = label
                      nutritionView.daysBack = selection
                  }
    }

    id: nutritionView

    title: "Nutrition"

    Rectangle {
        anchors {
            top: nav.bottom
            left: parent.left
            right: parent.right

            margins: 8 * Constants.scalar
        }

        id: combo

        color: Constants.sub

        implicitHeight: 45 * Constants.scalar

        MouseArea {
            anchors.fill: parent
            onClicked: backDialog.open()

            RowLayout {
                anchors {
                    fill: parent

                    rightMargin: 10 * Constants.scalar
                }

                Text {
                    id: viewLabel

                    Layout.fillWidth: true
                    Layout.leftMargin: 15 * Constants.scalar

                    color: Constants.text

                    text: "Today"

                    font.pixelSize: 16 * Constants.scalar

                    horizontalAlignment: Text.AlignHCenter
                }
            }
        }
    }

    RowLayout {
        id: header
        anchors {
            top: combo.bottom
            left: parent.left
            right: parent.right

            topMargin: 8 * Constants.scalar
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
