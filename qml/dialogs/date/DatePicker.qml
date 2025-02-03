import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

AnimatedDialog {
    id: datePicker

    property alias currentDate: days.currentDate

    title: "Select Date"

    width: 420 * Constants.scalar
    height: 500 * Constants.scalar

    standardButtons: Dialog.Ok | Dialog.Cancel

    ColumnLayout {
        anchors.fill: parent
        anchors.topMargin: 5

        YearSpinBox {
            Layout.fillWidth: true
            bindTarget: days
            bindedProperty: "year"
        }

        MonthSpinBox {
            Layout.fillWidth: true
            bindTarget: days
            bindedProperty: "month"
        }

        DayOfWeekRow {
            id: week
            Layout.fillWidth: true

            delegate: Text {
                text: shortName
                font: week.font
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                color: Constants.text

                required property string shortName
            }
        }

        MonthGrid {
            id: days
            Layout.fillWidth: true
            Layout.fillHeight: true

            month: currentDate.getMonth()

            // year: currentDate.getFullYear()
            onMonthChanged: currentDate.setMonth(month)
            onYearChanged: currentDate.setFullYear(year)

            property date currentDate

            Component.onCompleted: {
                let newDate = new Date()
                // slightly hacky way to ensure the timezone is correct
                newDate.setUTCMinutes(newDate.getMinutes())
                currentDate = newDate
            }

            delegate: Text {
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                opacity: model.month === days.month ? 1 : 0.5
                text: model.day
                font: days.font

                color: Constants.text

                Rectangle {
                    anchors.fill: parent
                    color: "lightblue"
                    visible: days.currentDate.getDate() === model.day
                             && days.currentDate.getMonth() === model.month
                    z: -2
                }
            }

            onClicked: date => {
                           let newDate = date
                           newDate.setUTCMinutes(
                               newDate.getUTCMinutes(
                                   ) + newDate.getTimezoneOffset())

                           month = date.getMonth()
                           year = date.getFullYear()

                           currentDate = date
                       }
        }
    }
}
