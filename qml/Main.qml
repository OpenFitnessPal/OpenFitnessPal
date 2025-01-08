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

    onClosing: (close) => {
        close.accepted = screen.back()
    }

    Component.onCompleted: {
        Constants.scalar = Math.min(width / Constants.width, height / Constants.height)
        Constants.isVertical = width < height
    }

    onWidthChanged: {
        Constants.scalar = Math.min(width / Constants.width, height / Constants.height)
        Constants.isVertical = width < height
    }

    onHeightChanged: {
        Constants.scalar = Math.min(width / Constants.width, height / Constants.height)
        Constants.isVertical = width < height
    }

    MainScreen {
        id: screen

        width: window.width
        height: window.height
    }
}
