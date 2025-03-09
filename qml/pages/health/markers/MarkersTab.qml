import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt.labs.qmlmodels

import OpenFitnessPal

BaseTab {
    id: markersTab

    title: "Health Markers"

    MarkerChoiceDialog {
        id: choice

        onChoice: choice => healthMarkerModel.add(choice)
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

        text: "Add Marker"
        onClicked: choice.open()

        background: Rectangle {
            color: button.pressed ? Constants.accentPressed : Constants.accent
            radius: 5 * Constants.scalar
        }
    }

    ListView {
        id: listView
        anchors {
            top: nav.bottom
            left: parent.left
            right: parent.right
            bottom: button.top

            topMargin: 10 * Constants.scalar
        }

        clip: true

        Component.onCompleted: healthMarkerModel.load()

        model: healthMarkerModel

        delegate: DelegateChooser {
            role: "name"
            DelegateChoice {
                roleValue: "RHR"

                HeartRateMarker {
                    width: listView.width
                }
            }

            DelegateChoice {
                roleValue: "Mile Time"

                MileTimeMarker {
                    width: listView.width
                }
            }

            DelegateChoice {
                roleValue: "Sleep"

                SleepMarker {
                    width: listView.width
                }
            }

            DelegateChoice {
                roleValue: "Blood Pressure"

                BloodPressureMarker {
                    width: listView.width
                }
            }

            DelegateChoice {
                roleValue: "VO2 Max"

                VO2MaxMarker {
                    width: listView.width
                }
            }
        }
    }
}
