import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

RowLayout {
    implicitHeight: 60 * Constants.scalar
    
    NavButton {
        label: "Delete"
        onClicked: sets.remove(idx)
    }
    
    LabeledSpinBox {
        editable: true
        label: "Reps"
        
        bindTarget: model
        bindedProperty: "reps"
        
        Layout.fillWidth: true
    }
    
    LabeledSpinBox {
        editable: true
        label: "Weight"
        
        bindTarget: model
        bindedProperty: "weight"
        
        Layout.fillWidth: true
    }
}
