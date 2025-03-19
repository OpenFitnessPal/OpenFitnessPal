import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

Rectangle {
    signal deleteRequested

    color: Constants.bg

    height: row.height + (messageField.lineCount
                          === 0 ? 30 * Constants.scalar : messageField.height)
            + 10 * Constants.scalar

    RowLayout {
        id: row
        implicitHeight: 50 * Constants.scalar

        NavButton {
            id: del
            label: "Delete"
            onClicked: deleteRequested()

            Layout.maximumWidth: 40 * Constants.scalar
        }

        TimeField {
            id: timeField

            Component.onCompleted: time = model.time
            onTimeChanged: model.time = time
        }
    }

    TextArea {
        id: messageField

        anchors {
            top: row.bottom
            left: parent.left
            right: parent.right

            topMargin: 10 * Constants.scalar
        }

        wrapMode: "WordWrap"

        text: model.message
        onEditingFinished: model.message = text

        font.pixelSize: 16 * Constants.scalar
    }
}
