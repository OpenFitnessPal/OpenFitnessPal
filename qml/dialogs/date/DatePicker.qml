import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import OFPItems

AnimatedDialog {
    id: datePicker

    property alias currentDate: days.currentDate

    title: "Select Date"

    width: 420 * Constants.scalar
    height: 420 * Constants.scalar

    standardButtons: Dialog.Ok | Dialog.Cancel

    ColumnLayout {
        anchors.fill: parent
        anchors.topMargin: 5

        RowLayout {
            Layout.fillWidth: true
            uniformCellSizes: true

            MonthSpinBox {
                Layout.fillWidth: true
                bindTarget: days
                bindedProperty: "month"
            }

            LabeledSpinBox {
                Layout.fillWidth: true
                bindTarget: days
                bindedProperty: "year"

                font.pixelSize: 20 * Constants.scalar

                label: "Year"

                textFromValue: function(value) {
                    return value;
                }
            }
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

            month: currentDate.getUTCMonth()
            year: currentDate.getUTCFullYear()

            onMonthChanged: currentDate.setUTCMonth(month)
            onYearChanged: currentDate.setUTCFullYear(year)

            property date currentDate: new Date()

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
                    visible: days.currentDate.getUTCDate() === model.day && days.currentDate.getUTCMonth() === model.month
                    z: -2
                }
            }

            onClicked: (date) => {
                           console.log(date)
                           month = date.getUTCMonth()
                           year = date.getUTCFullYear()

                           currentDate = date;
                       }
        }
    }
}
