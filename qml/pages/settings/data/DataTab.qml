import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt.labs.platform

import OpenFitnessPal

BaseTab {
    id: data

    title: "Data"

    color: Constants.bg

    FileDialog {
        id: backupDialog
        folder: StandardPaths.writableLocation(StandardPaths.DownloadLocation)
        onAccepted: backupManager.backup(file)
        defaultSuffix: "zip"
        nameFilters: ["Zip files (*.zip)"]
        fileMode: FileDialog.SaveFile
    }

    FileDialog {
        id: restoreDialog
        folder: StandardPaths.writableLocation(StandardPaths.DownloadLocation)
        onAccepted: {
            console.log(folder, files)
            backupManager.restore(folder, file)

            // hacky way to forcefully reload everything
            dateManager.date = new Date(0)
            dateManager.date = new Date()

            recipeEditModel.load()
        }
        // nameFilters: ["Zip files (*.zip)"]
        fileMode: FileDialog.OpenFile
    }

    ColumnLayout {
        anchors {
            top: nav.bottom
            left: parent.left
            right: parent.right

            topMargin: 25 * Constants.scalar
        }

        BetterButton {
            Layout.fillWidth: true
            name: "Backup Data"

            onClicked: backupDialog.open()
        }

        BetterButton {
            Layout.fillWidth: true
            name: "Restore from Backup"

            onClicked: restoreDialog.open()
        }
    }
}
