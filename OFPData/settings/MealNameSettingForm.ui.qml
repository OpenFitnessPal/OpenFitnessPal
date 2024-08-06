import QtQuick 6.2
import QtQuick.Controls 6.2
import QtQuick.Layouts 6.2

import OFPData

RowLayout {
    signal mealNamesChanged

    required property int mealNumber
    required property string defaultName

    property alias mealName: mealName

    Text {
        id: mealText
        color: "#ffffff"
        text: qsTr("Meal " + mealNumber + " Name:")

        anchors.leftMargin: 20
        anchors.topMargin: 10

        font: Constants.underlinedSubtitleFont
    }

    TextField {
        id: mealName
        height: 35
        color: "#ffffff"

        font: Constants.largeFont
        Layout.fillWidth: true
    }
}
