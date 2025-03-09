import QtQuick 2.15
import QtQuick.Layouts

import OpenFitnessPal

RowLayout {
    property date time

    function pad(num) {
        if (num >= 10)
            return num
        return "0" + num
    }

    SmallNumberField {
        id: hours

        bindTarget: null
        bindedProperty: null

        text: time.getHours()
        onTextEdited: time.setHours(text)

        label: ""

        from: 0
        to: 23

        attentive: false

        implicitWidth: 40 * Constants.scalar
    }

    Text {
        font.pixelSize: 14 * Constants.scalar

        color: Constants.text

        text: ":"
    }

    SmallNumberField {
        id: mins

        bindTarget: null
        bindedProperty: null

        text: pad(time.getMinutes())
        onTextEdited: time.setMinutes(text)

        label: ""

        from: 0
        to: 59

        attentive: false

        implicitWidth: 40 * Constants.scalar
    }
}
