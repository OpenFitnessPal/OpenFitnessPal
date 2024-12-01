pragma Singleton

import QtQuick 6.2

QtObject {
    readonly property int width: 480
    readonly property int height: 640
    readonly property int pageHeight: 640 - 50

    property string relativeFontDirectory: "fonts"

    /* Edit this comment to add your custom font */
    readonly property font tinyFont: Qt.font({
                                                 "family": Qt.application.font.family,
                                                 "pixelSize": Qt.application.font.pixelSize * 1.2
                                             })

    readonly property font smallFont: Qt.font({
                                                  "family": Qt.application.font.family,
                                                  "pixelSize": Qt.application.font.pixelSize * 1.2
                                              })

    readonly property font mediumFont: Qt.font({
                                                   "family": Qt.application.font.family,
                                                   "pixelSize": Qt.application.font.pixelSize * 1.4
                                               })

    readonly property font underlinedMediumFont: Qt.font({
                                                             "family": Qt.application.font.family,
                                                             "pixelSize": Qt.application.font.pixelSize * 1.4,
                                                             "underlined": true
                                                         })

    readonly property font boldMediumFont: Qt.font({
                                                       "family": Qt.application.font.family,
                                                       "pixelSize": Qt.application.font.pixelSize
                                                                    * 1.4,
                                                       "bold": true
                                                   })

    readonly property font largeFont: Qt.font({
                                                  "family": Qt.application.font.family,
                                                  "pixelSize": Qt.application.font.pixelSize * 1.6
                                              })

    readonly property font boldLargeFont: Qt.font({
                                                      "family": Qt.application.font.family,
                                                      "pixelSize": Qt.application.font.pixelSize
                                                                   * 1.6,
                                                      "weight": Font.DemiBold
                                                  })

    readonly property font subSubtitleFont: Qt.font({
                                                        "family": Qt.application.font.family,
                                                        "pixelSize": Qt.application.font.pixelSize
                                                                     * 1.5
                                                    })

    readonly property font subtitleFont: Qt.font({
                                                     "family": Qt.application.font.family,
                                                     "pixelSize": Qt.application.font.pixelSize
                                                                  * 1.8
                                                 })

    readonly property font boldSubtitleFont: Qt.font({
                                                         "family": Qt.application.font.family,
                                                         "pixelSize": Qt.application.font.pixelSize
                                                                      * 1.8,
                                                         "weight": Font.DemiBold
                                                     })

    readonly property font mediumSubtitleFont: Qt.font({
                                                           "family": Qt.application.font.family,
                                                           "pixelSize": Qt.application.font.pixelSize * 1.8,
                                                           "weight": Font.Medium
                                                       })

    readonly property font underlinedSubtitleFont: Qt.font({
                                                               "family": Qt.application.font.family,
                                                               "pixelSize": Qt.application.font.pixelSize * 1.8,
                                                               "underline": true
                                                           })

    readonly property font titleFont: Qt.font({
                                                  "family": Qt.application.font.family,
                                                  "pixelSize": Qt.application.font.pixelSize * 2,
                                                  "bold": true
                                              })

    readonly property color baseColor: "#000000"
    readonly property color sub1Color: "#141414"
    readonly property color sub2Color: "#282828"
    readonly property color sub3Color: "#424242"
}
