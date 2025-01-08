import QtQuick
import QtQuick.Controls

// StackView that implements proper transitions
StackView {
    id: stackView

    clip: true

    pushEnter: Transition {
        PropertyAnimation {
            property: "opacity"
            from: 0
            to: 1
            duration: 300
        }
        PropertyAnimation {
            property: "x"
            from: stackView.width
            to: 0
            duration: 300
            easing.type: Easing.InOutQuad
        }
    }
    pushExit: Transition {
        PropertyAnimation {
            property: "opacity"
            from: 1
            to: 0
            duration: 300
        }
        PropertyAnimation {
            property: "x"
            from: 0
            to: -stackView.width
            duration: 300
            easing.type: Easing.InOutQuad
        }
    }

    popEnter: Transition {
        PropertyAnimation {
            property: "opacity"
            from: 0
            to: 1
            duration: 300
        }
        PropertyAnimation {
            property: "x"
            from: -stackView.width
            to: 0
            duration: 300
            easing.type: Easing.InOutQuad
        }
    }
    popExit: Transition {
        PropertyAnimation {
            property: "opacity"
            from: 1
            to: 0
            duration: 300
        }
        PropertyAnimation {
            property: "x"
            from: 0
            to: stackView.width
            duration: 300
            easing.type: Easing.InOutQuad
        }
    }
}
