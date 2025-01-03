import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs

import QtQuick.Controls.Universal

import OpenFitnessPal

Window {
    id: window
    width: Constants.width
    height: Constants.height
    visible: true
    title: "OpenFitnessPal"

    Universal.theme: Universal.Dark
    Universal.accent: "Crimson"

    Component.onCompleted: {
        Constants.scalar = Math.max(width / Constants.width, height / Constants.height)
        Constants.isVertical = width < height
    }

    MainScreen {
        id: screen
    }
}
