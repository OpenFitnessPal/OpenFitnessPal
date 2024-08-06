import QtQuick 2.15
import QtCore

DirSettingForm {
    function updateDir(selectedDir) {
        if (isCache) {
            settings.set("cacheDir", selectedDir)
            settings.mvCacheDir(selectedDir)
        } else {
            settings.set("dataDir", selectedDir)
            settings.mvDataDir(selectedDir)
        }
    }

    function updateDirFromDialog() {
        let selectedDir = dirSelect.selectedFolder
        dir.text = selectedDir
        updateDir(selectedDir)
    }

    function updateDirFromText() {
        let selectedDir = dir.text
        updateDir(selectedDir)
    }

    button.onClicked: {
        dirSelect.currentFolder = settings.get(isCache ? "cacheDir" : "dataDir")
        dirSelect.open()

        dirSelect.accepted.connect(updateDirFromDialog)
    }

    dir.onEditingFinished: updateDirFromText()

    Component.onCompleted: {
        let settingName = isCache ? "cacheDir" : "dataDir";

        let setting = settings.get(settingName)
        if (typeof setting == "undefined") {
            setting = StandardPaths.writableLocation(isCache ? StandardPaths.CacheLocation : StandardPaths.AppLocalDataLocation)
            settings.set(settingName, setting)
        }

        dir.text = setting
    }
}
