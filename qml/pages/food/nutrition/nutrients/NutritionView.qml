import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

Item {
    property bool weekView

    id: nutritionView

    NutritionHeader {
        id: header

        anchors {
            top: parent.top
            left: parent.left
            right: parent.right

            margins: 8 * Constants.scalar
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

            weekView: nutritionView.weekView
        }
    }
}
