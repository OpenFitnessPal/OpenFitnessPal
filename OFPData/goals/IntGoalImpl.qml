import QtQuick 2.15
import QtQuick.Controls 2.15

IntGoalForm {
    width: parent.width

    property int internalName: "goal"

    spinBox.onValueChanged: goalManager[internalName] = spinBox.value
}
