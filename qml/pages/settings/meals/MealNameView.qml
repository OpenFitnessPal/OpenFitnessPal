import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

Rectangle {
    id: nameView

    property bool selected: false

    border {
        width: 5
        color: selected ? "lightgreen" : "transparent"
    }

    color: Constants.dialog

    height: 60 * Constants.scalar

    RowLayout {
        spacing: 10
        anchors.fill: parent

        MouseArea {
            id: mouseArea

            Layout.preferredWidth: 40 * Constants.scalar
            Layout.preferredHeight: 40 * Constants.scalar

            drag.axis: Drag.YAxis
            onPressed: {
                listView.currentIndex = model.idx
                listView.interactive = false
                swipe.interactive = false
            }

            onReleased: (mouse) => {
                            listView.interactive = true
                            swipe.interactive = true
                            let from = model.idx

                            let fixedPos = mapToItem(listView.contentItem, mouse.x, mouse.y)
                            let to = listView.indexAt(fixedPos.x, fixedPos.y)

                            for (let i = 0; i < listView.count; ++i) {
                                listView.itemAtIndex(i).selected = false
                            }

                            if (to === -1) return;

                            if (from !== to) {
                                mealNamesModel.move(from, to);
                            }
                        }

            onMouseYChanged: (mouse) => {
                let fixedPos = mapToItem(listView.contentItem, mouse.x, mouse.y)
                let to = listView.indexAt(fixedPos.x, fixedPos.y)

                if (to !== -1) {
                    for (let i = 0; i < listView.count; ++i) {
                        listView.itemAtIndex(i).selected = (i === to)
                    }
                }
            }

            Image {
                anchors.centerIn: parent
                source: "qrc:/Reorder"
            }
        }

        IconButton {
            id: remove

            label: "Delete"
            onClicked: mealNamesModel.remove(model.idx);
        }

        TextField {
            Layout.fillWidth: true
            text: model.name

            font.pixelSize: Math.round(30 * Constants.scalar)
        }
    }
}
