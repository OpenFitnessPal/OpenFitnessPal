import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

BaseSettingsTab {
    signal add(int mealNumber, var serving)

    property int mealNumber: 0

    id: foodSearch

    title: "Search"

    function search() {
        swipeView.currentItem.search(searchText.text)
    }

    Shortcut {
        sequence: Qt.Key_Return
        onActivated: search()
    }

    ColumnLayout {
        anchors {
            top: nav.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom

            margins: 8 * Constants.scalar
        }

        RowLayout {
            Layout.fillWidth: true

            TextField {
                id: searchText

                Layout.fillWidth: true
                placeholderText: "Search for a Food"

                font.pixelSize: 18 * Constants.scalar
                color: Constants.text

                background: Rectangle {
                    color: Constants.bg
                    width: parent.width
                    border.color: Constants.text
                    border.width: 1
                    radius: 5 * Constants.scalar
                }

                onAccepted: search()
            }

            Button {
                id: btn

                hoverEnabled: true

                property bool mousedOver: highlighted || hovered || down

                text: "Submit"
                onClicked: swipeView.currentItem.search(searchText.text)

                contentItem: Text {
                    color: Constants.text
                    font.pixelSize: 18 * Constants.scalar

                    text: btn.text
                }

                background: Rectangle {
                    implicitWidth: 32
                    implicitHeight: 32

                    radius: 4 * Constants.scalar
                    visible: !btn.flat || btn.down || btn.checked
                             || btn.highlighted
                    color: (btn.mousedOver) ? Constants.buttonHighlighted : Constants.button
                }
            }
        }

        TabBar {
            id: tabBar

            Layout.fillWidth: true
            implicitHeight: 48 * Constants.scalar

            position: "Header"
            currentIndex: swipeView.currentIndex

            background: Rectangle {
                color: Constants.sub
            }

            Repeater {
                model: ["Online", "History", "Recipes"]

                TabButton {
                    text: modelData

                    font.pixelSize: 16 * Constants.scalar
                }
            }
        }

        SwipeView {
            id: swipeView

            Layout.fillWidth: true
            Layout.fillHeight: true

            clip: true
            currentIndex: tabBar.currentIndex

            FoodSearchPage {
                id: online

                offlineSearch: false
                onAdd: serving => foodSearch.add(mealNumber, serving)
            }

            FoodSearchPage {
                id: offline

                offlineSearch: true
                onAdd: serving => foodSearch.add(mealNumber, serving)
            }
        }
    }

    BusyIndicator {
        id: busy
        running: false
        anchors.centerIn: parent
    }
}
