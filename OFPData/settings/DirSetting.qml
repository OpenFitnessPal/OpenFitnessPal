import QtQuick 2.15
import QtQuick.Dialogs
import QtCore

DirSettingForm {
    signal reloadData

    property string dirToSwitch

    function updateDir(selectedDir, transfer) {
        if (isCache) {
            settings.set("cacheDir", selectedDir)
            if (transfer) {
                settings.mvCacheDir(selectedDir)
            } else {
                settings.newCacheDir(selectedDir)
            }
        } else {
            settings.set("dataDir", selectedDir)
            if (transfer) {
                settings.mvDataDir(selectedDir)
            } else {
                settings.newDataDir(selectedDir)
            }
        }

        dir.text = selectedDir
    }

    function handleButton(button, role) {
        dataConfirm.buttonClicked.disconnect(handleButton)

        switch (button) {
        case MessageDialog.Yes:
            updateDir(dirToSwitch, true)
            break
        case MessageDialog.No:
            updateDir(dirToSwitch, false)
            break
        case MessageDialog.Cancel:
        default:
            break
        }

        reloadData()
    }

    function confirmSwitch(selectedDir) {
        let needsConfirmation = false
        if (isCache) {
            needsConfirmation = settings.cacheExists(selectedDir)
        } else {
            needsConfirmation = settings.dataExists(selectedDir)
        }

        if (needsConfirmation) {
            dirToSwitch = selectedDir
            dataConfirm.buttonClicked.connect(handleButton)
            dataConfirm.open()
        } else {
            updateDir(selectedDir, true)
        }
    }

    function updateDirFromDialog() {
        let selectedDir = dirSelect.selectedFolder.toString()

        let path = selectedDir.replace(/^(file:\/{2})/,"");
        let cleanPath = decodeURIComponent(path);

        confirmSwitch(cleanPath)
    }

    function updateDirFromText() {
        let selectedDir = dir.text
        confirmSwitch(selectedDir)
    }

    button.onClicked: {
        dirSelect.currentFolder = "file://" + dir.text.trim()
        dirSelect.open()

        dirSelect.accepted.connect(updateDirFromDialog)
    }

    dir.onEditingFinished: updateDirFromText()

    Component.onCompleted: {
        let settingName = isCache ? "cacheDir" : "dataDir";

        let setting = settings.get(settingName)
        if (typeof setting == "undefined") {
            setting = StandardPaths.writableLocation(isCache ? StandardPaths.CacheLocation : StandardPaths.AppLocalDataLocation).toString()

            let path = setting.replace(/^(file:\/{2})/,"");
            let cleanPath = decodeURIComponent(path);

            setting = cleanPath

            settings.set(settingName, setting)
        }

        dir.text = setting
    }
}
