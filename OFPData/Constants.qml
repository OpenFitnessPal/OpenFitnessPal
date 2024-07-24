pragma Singleton
import QtQuick 6.2
import QtQuick.Studio.Application

QtObject {
    readonly property int width: 480
    readonly property int height: 640
    readonly property int pageHeight: 640 - 50

    property string relativeFontDirectory: "fonts"

    /* Edit this comment to add your custom font */
    readonly property font font: Qt.font({
                                             family: Qt.application.font.family,
                                             pixelSize: Qt.application.font.pixelSize
                                         })
    readonly property font largeFont: Qt.font({
                                                  family: Qt.application.font.family,
                                                  pixelSize: Qt.application.font.pixelSize * 1.6
                                              })

    readonly property color baseColor: "#000000"
    readonly property color sub1Color: "#141414"
    readonly property color sub2Color: "#282828"


    property StudioApplication application: StudioApplication {
        fontPath: Qt.resolvedUrl("../../OFPContent/" + relativeFontDirectory)
    }
}
