pragma Singleton

import QtQuick
import QtQuick.Controls.Universal

QtObject {
    readonly property int width: 420
    readonly property int height: 840

    property color accent: "red"
    property color accentPressed: "#ff5252"

    readonly property color bg: "#111111"
    readonly property color dialog: "#222222"
    readonly property color sub: "#222222"

    readonly property color button: "#333333"
    readonly property color buttonHighlighted: "#777777"

    readonly property color text: "#EEEEEE"

    property double scalar: 1.0
    property bool isVertical: false
}
