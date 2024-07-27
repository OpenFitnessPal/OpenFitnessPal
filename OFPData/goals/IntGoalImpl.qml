import QtQuick 2.15
import QtQuick.Controls 2.15

IntGoalForm {
    id: impl
    width: parent.width

    function sendValue() {
        console.log("Value Changed for " + name + " to " + spinBox.value)
        impl.value = spinBox.value
        impl.goalValueChanged(spinBox.value)

        if (isValid) {
            goalManager.setValue(internalName, spinBox.value)
        }
    }

    Component.onCompleted: {
        let val = goalManager.getValue(internalName)
        if (typeof val !== 'undefined') {
            impl.value = goalManager.getValue(internalName)
            spinBox.value = impl.value
        }

        spinBox.valueChanged.connect(sendValue)
    }
}
