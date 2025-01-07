import QtQuick
import QtQuick.Controls
import QtQuick.Layouts 6.6

import OFPItems

Rectangle {
    id: screen

    color: Constants.bg

    function back() {
        return swipe.back()
    }

    DateSelector {
        id: dateSelect

        anchors {
            top: parent.top
            left: parent.left
            right: parent.right

            margins: 4
        }

        onPickDate: {
            picker.currentDate = currentDate
            picker.open()
        }
    }

    DatePicker {
        id: picker

        onAccepted: {
            dateSelect.currentDate = currentDate
        }
    }

    SwipeView {
        id: swipe

        function back() {
            // if false, there was no operation to be done
            if (!currentItem.back()) {
                // TODO: make it go to previous page
                // if no previous page, exit
                console.log("UNIMPLEMENTED")

                // return false to NOT accept the close event, true to accept
                return true
            }

            return false
        }

        anchors {
            top: dateSelect.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

        SettingsPage {
            id: settings
        }
    }
}
