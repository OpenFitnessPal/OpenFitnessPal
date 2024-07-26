import QtQuick 2.15
import QtQuick.Controls 2.15

IntGoalForm {
    id: impl
    width: parent.width

    spinBox.onValueChanged: (value) => impl.goalValueChanged(value)

    // spinBox.onValueChanged: if (isValid) goalManager[internalName] = spinBox.value

    // Component.onCompleted: spinBox.value = goalManager[internalName]
}
