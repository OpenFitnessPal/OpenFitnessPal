import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OpenFitnessPal

AnimatedDialog {
    id: datePicker

    title: "Select Date"

    width: 420 * Constants.scalar
    height: 500 * Constants.scalar

    standardButtons: Dialog.Close

    ColumnLayout {
        anchors.fill: parent
        anchors.topMargin: 5

        TextButton {
            id: btn

            name: "Today"

            onClicked: dateManager.date = new Date()
        }

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

            property date currentDate: dateManager.date

            onMonthChanged: {
                let newDate = currentDate
                newDate.setMonth(month)
                dateManager.date = newDate
            }
            onYearChanged: {
                let newDate = currentDate
                newDate.setFullYear(year)
                dateManager.date = newDate
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
                    visible: days.currentDate.getUTCDate() === model.day
                             && days.currentDate.getUTCMonth() === model.month
                    z: -2
                }
            }

            onClicked: date => {
                           let newDate = date

                           newDate.setUTCMinutes(
                               newDate.getMinutes(
                                   ) + newDate.getTimezoneOffset())

                           month = newDate.getMonth()
                           year = newDate.getFullYear()

                           dateManager.date = newDate
                       }
        }
    }
}
