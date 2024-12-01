import QtQuick 2.15
import QtQuick.Controls 2.15

IntGoalForm {
    id: impl
    width: parent.width

    function sendValue() {
        impl.value = spinBox.value
        impl.goalValueChanged(spinBox.value)

        if (isValid) {
            goalManager.set(internalName, spinBox.value)
        }
    }

    function setValue(newValue) {
        spinBox.valueChanged.disconnect(sendValue)

        spinBox.value = newValue
        impl.value = newValue

        spinBox.valueChanged.connect(sendValue)
    }

    Component.onCompleted: {
        let val = goalManager.get(internalName, defaultValue)
        if (typeof val !== 'undefined') {
            impl.value = val
            spinBox.value = impl.value
        }

        spinBox.valueChanged.connect(sendValue)
    }
}
