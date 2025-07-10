import QtQuick 2.15
import QtQuick.Layouts

import OpenFitnessPal

RowLayout {
    id: hmsField

    // seconds
    property int time: 0

    function resetTime() {
        time = hours * 3600 + minutes * 60 + seconds
    }

    property int setTime
    onSetTimeChanged: {
        let hours = Math.floor(setTime / 3600)
        if (!useHours) {
            setTime -= hours * 3600
            hours = 0
        }

        let minutes = Math.floor((setTime - hours * 3600) / 60)
        if (!useMinutes) {
            setTime -= minutes * 60
            minutes = 0
        }

        let seconds = (setTime - hours * 3600 - minutes * 60)
        if (!useSeconds) {
            setTime -= seconds
            seconds = 0
        }

        this.hours = hours
        this.minutes = minutes
        this.seconds = seconds

        resetTime()
    }

    property int hours: 0
    property int minutes: 0
    property int seconds: 0

    property bool useHours: true
    property bool useMinutes: true
    property bool useSeconds: true

    property bool labeled

    SmallNumberField {
        visible: useHours

        bindTarget: hmsField
        bindedProperty: "hours"

        label: labeled ? "h" : ""

        from: 0
        to: 23

        attentive: false

        onEditingFinished: resetTime()

        implicitWidth: (labeled ? 55 : 40) * Constants.scalar
    }

    Text {
        visible: useHours && (useMinutes || useSeconds)

        font.pixelSize: 14 * Constants.scalar

        color: Constants.text

        text: ":"
    }

    SmallNumberField {
        visible: useMinutes

        bindTarget: hmsField
        bindedProperty: "minutes"

        label: labeled ? "m" : ""

        from: 0
        to: 59

        attentive: false
        onEditingFinished: resetTime()

        implicitWidth: (labeled ? 55 : 40) * Constants.scalar
    }

    Text {
        visible: useSeconds && useMinutes

        font.pixelSize: 14 * Constants.scalar

        color: Constants.text

        text: ":"
    }

    SmallNumberField {
        visible: useSeconds

        bindTarget: hmsField
        bindedProperty: "seconds"

        label: labeled ? "s" : ""

        from: 0
        to: 59

        attentive: false
        onEditingFinished: resetTime()

        implicitWidth: (labeled ? 55 : 40) * Constants.scalar
    }
}
