import QtQuick 2.15
import QtQuick.Layouts

import OpenFitnessPal

RowLayout {
    property date time
    property bool labeled: false

    function pad(num) {
        if (num >= 10)
            return num
        return "0" + num
    }

    SmallNumberField {
        bindTarget: null
        bindedProperty: null

        text: (isNaN(time.getMinutes())
               || time === null) ? 0 : time.getMinutes()
        onTextEdited: {
            if (time === null || isNaN(time)) {
                time = new Date(0, 0, 0, 0, text, 0)
            } else {
                time.setMinutes(text)
            }
        }

        label: labeled ? "m" : ""

        from: 0
        to: 59

        attentive: false

        implicitWidth: (labeled ? 50 : 40) * Constants.scalar
    }

    Text {
        font.pixelSize: 14 * Constants.scalar

        color: Constants.text

        text: ":"
    }

    SmallNumberField {
        bindTarget: null
        bindedProperty: null

        text: (isNaN(time.getSeconds())
               || time === null) ? 0 : pad(time.getSeconds())
        onTextEdited: {
            if (time === null || isNaN(time)) {
                time = new Date(0, 0, 0, 0, 0, text)
                time.setMinutes(0)
            } else {
                time.setSeconds(text)
            }
        }

        label: labeled ? "s" : ""

        from: 0
        to: 59

        attentive: false

        implicitWidth: (labeled ? 50 : 40) * Constants.scalar
    }
}
