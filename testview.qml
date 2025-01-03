StackView {
        id: stackView
        width: 200
        height: 200
        anchors.centerIn: parent
        initialItem: firstPage

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

        Rectangle {
            id: firstPage
            color: "red"
            Button {
                id: b1
                anchors.centerIn: parent
                text: "Go to Second Page"
                onClicked: stackView.push(secondPage)
            }

            Button {
                anchors.top: b1.bottom
                anchors.horizontalCenter: b1.horizontalCenter
                text: "Go to Third Page"
                onClicked: stackView.push(thirdPage)
            }
        }

        Rectangle {
            visible: false
            id: secondPage
            color: "blue"
            Button {
                anchors.centerIn: parent
                text: "Go back"
                onClicked: stackView.pop()
            }
        }

        Rectangle {
            visible: false
            id: thirdPage
            color: "purple"
            Button {
                anchors.centerIn: parent
                text: "Go back"
                onClicked: stackView.pop()
            }
        }
    }
