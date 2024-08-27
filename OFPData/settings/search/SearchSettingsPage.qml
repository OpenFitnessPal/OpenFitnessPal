import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs

import OFPNative
import OFPData

SearchSettingsPageForm {
    id: impl
    signal goBack

    function addFilter() {

    }

    NutrientModel {
        id: nm
    }

    Dialog {
        id: list
        width: impl.width
        height: impl.height

        property alias view: view

        NutrientModel {
            id: nm2
        }

        RemoveButton {
            id: back

            anchors.left: parent.left
            anchors.top: parent.top

            anchors.leftMargin: 8
            anchors.topMargin: 8

            onClicked: list.close()
        }

        ListView {
            id: view
            clip: true

            anchors {
                top: back.bottom
                left: parent.left
                right: parent.right
                bottom: parent.bottom

                topMargin: 8
                leftMargin: 8
                rightMargin: 8
                bottomMargin: 8
            }

            model: nm2
            delegate: Rectangle {
                clip: true
                color: Constants.sub1Color
                height: 50
                width: parent.width

                border.width: 2
                border.color: "#ffffff"

                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        nm.add(model.name, model.displayName, model.suffix)
                        list.close()
                    }

                    Text {
                        text: model.displayName
                        anchors.fill: parent

                        anchors.leftMargin: 15

                        verticalAlignment: Text.AlignVCenter

                        font: Constants.largeFont
                        color: "#ffffff"
                    }
                }
            }
        }

        function openUp() {
            nm2.loadUnfilteredData()
            open()
        }
    }


    remove.onClicked: goBack()
    add.onClicked: list.openUp()

    filters.height: 60 * filters.count
    filters.model: nm
    filters.delegate: NutrientFilter {
        width: filters.width
        height: 60

        remove.onClicked: {
            settings.rm("avoid_" + model.name)
            nm.removeRow(model.ntID)
        }

        threshold.onValueChanged: {
            model.filter = threshold.value / 100.0
        }
    }

    Component.onCompleted: {
        generics.checked = settings.get("generics")
        results.value = settings.get("results")
        nm.loadFilterData()
    }

    generics.onCheckedChanged: settings.set("generics", generics.checked)
    results.onValueChanged: settings.set("results", results.value)
}
