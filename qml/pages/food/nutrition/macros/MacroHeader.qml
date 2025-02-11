import QtQuick
import QtQuick.Shapes
import QtQuick.Controls
import QtQuick.Layouts
import QtCharts

import OpenFitnessPal

RowLayout {
    Layout.fillWidth: true
    
    uniformCellSizes: true
    
    Repeater {
        model: 3
        Item {
            Layout.fillWidth: true
        }
    }
    
    Repeater {
        model: ["Total", "Percent", "Goal"]
        
        Text {
            text: modelData
            color: Constants.text
            
            font.pixelSize: 14 * Constants.scalar
            
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignBottom
        }
    }
}
