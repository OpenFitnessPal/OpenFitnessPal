    Accelerometer {
        id: accel

        property int stepCount: 0
        property bool isStepInProgress: false

        function detectStep(z) {
            if (z > 5 && !isStepInProgress) {
                isStepInProgress = true;
            } else if (z < -5 && isStepInProgress) {
                stepCount++;
                isStepInProgress = false;
            }
        }

        dataRate: 50
        active: true

        onReadingChanged: {
            var z = reading.z;
            console.log("yoyoyo")
            detectStep(z);
        }
    }

    Text {
        color: Constants.text
        anchors.centerIn: parent
        width: parent.width

        font.pixelSize: 30 * Constants.scalar

        text: "Steps:\n" + accel.stepCount // accel.reading.x + "\n" + accel.reading.y + "\n" + accel.reading.z
        wrapMode: Text.WordWrap
    }
