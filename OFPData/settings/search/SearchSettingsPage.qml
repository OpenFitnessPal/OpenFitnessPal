import QtQuick 2.15

SearchSettingsPageForm {
    signal goBack

    remove.onClicked: goBack()
}
