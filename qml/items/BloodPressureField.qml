import QtQuick 2.15
import QtQuick.Layouts

import OpenFitnessPal

RowLayout {
    property string value

    function resetValue() {
        value = sys.text + "/" + dia.text
    }

    SmallNumberField {
        id: sys

        bindTarget: null
        bindedProperty: null

        text: value.split("/")[0]
        onTextEdited: resetValue()

        label: ""

        from: 0
        to: 999

        attentive: false

        implicitWidth: 60 * Constants.scalar
    }

    Text {
        font.pixelSize: 16 * Constants.scalar

        color: Constants.text

        text: "/"
    }

    SmallNumberField {
        id: dia

        bindTarget: null
        bindedProperty: null

        text: value.split("/")[1]
        onTextEdited: resetValue()

        label: ""

        from: 0
        to: 999

        attentive: false

        implicitWidth: 60 * Constants.scalar
    }
}
