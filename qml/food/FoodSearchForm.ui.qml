

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15

import OpenFitnessPal

Rectangle {
    id: rectangle
    color: Constants.sub1Color

    property alias back: back
    property alias submit: submit

    property alias online: online
    property alias offline: offline
    property alias recipes: recipes

    property alias swipeView: swipeView
    property alias searchBar: searchBar

    Text {
        id: text1
        color: "#ffffff"
        text: qsTr("Food Search")
        anchors.top: parent.top
        anchors.topMargin: 10
        font: Constants.titleFont
        anchors.horizontalCenter: parent.horizontalCenter
    }

    TabBar {
        id: tabBar
        height: 48
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: text1.bottom
        anchors.leftMargin: 0
        anchors.rightMargin: 0
        anchors.topMargin: 53

        position: TabBar.Header
        currentIndex: swipeView.currentIndex

        TabButton {
            text: qsTr("Online")
        }
        TabButton {
            text: qsTr("Offline")
        }
        TabButton {
            text: qsTr("Recipes")
        }
    }

    SwipeView {
        id: swipeView
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: tabBar.bottom
        anchors.bottom: parent.bottom
        anchors.leftMargin: 15
        anchors.rightMargin: 15
        anchors.topMargin: 15
        anchors.bottomMargin: 15
        clip: true

        objectName: "swipeView"
        currentIndex: tabBar.currentIndex

        ListView {
            id: online
            clip: true
        }

        ListView {
            id: offline
            clip: true
        }

        ListView {
            id: recipes
            clip: true
        }
    }

    Button {
        id: back
        width: 50
        height: 50
        text: qsTr("<")
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 8
        anchors.topMargin: 0
        font.pointSize: 26
    }

    TextField {
        id: searchBar
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: back.bottom
        anchors.bottom: tabBar.top
        anchors.leftMargin: 10
        anchors.rightMargin: 80
        anchors.topMargin: 4
        anchors.bottomMargin: 6
        placeholderText: qsTr("Query")
    }

    ToolButton {
        id: submit

        text: qsTr("Submit")
        anchors.right: parent.right
        anchors.left: searchBar.right
        anchors.top: searchBar.top
        anchors.bottom: searchBar.bottom

        anchors.leftMargin: 8
        anchors.rightMargin: 8
        anchors.topMargin: 0
        anchors.bottomMargin: 0
        flat: false
    }
}
