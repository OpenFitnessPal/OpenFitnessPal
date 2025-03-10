import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

import OpenFitnessPal

BaseTab {
    id: data

    title: "Data"

    color: Constants.bg

    FileDialog {
        id: backupDialog
        currentFolder: StandardPaths.writableLocation(
                           StandardPaths.DownloadLocation)
        onAccepted: backupManager.backup(selectedFile)
        defaultSuffix: "zip"
        nameFilters: ["Zip files (*.zip)"]
        fileMode: FileDialog.SaveFile
    }

    FileDialog {
        id: restoreDialog
        currentFolder: StandardPaths.writableLocation(
                           StandardPaths.DownloadLocation)
        onAccepted: {
            backupManager.restore(selectedFile)

            // hacky way to forcefully reload everything
            dateManager.date = new Date(0)
            dateManager.date = new Date()
        }
        nameFilters: ["Zip files (*.zip)"]
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
