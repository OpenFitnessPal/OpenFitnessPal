

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15

import OFPData

Rectangle {
    id: rectangle
    y: 0
    width: Constants.width
    height: Constants.pageHeight
    color: Constants.baseColor

    property date currentDate

    property alias swipe: swipe
    property alias exercises: exercises
    property alias routines: routines
    property alias routineEdit: routineEdit

    SwipeView {
        id: swipe
        clip: true
        anchors.fill: parent
        anchors.bottomMargin: 40
        interactive: false
        currentIndex: 0

        ExercisePage {
            id: exercises
            visible: true
        }

        RoutinesPage {
            id: routines
        }
        
        ExerciseRoutineEdit {
            id: routineEdit
        }
    }
}
