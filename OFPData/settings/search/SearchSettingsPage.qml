import QtQuick 2.15

import OFPNative

SearchSettingsPageForm {
    signal goBack

    NutrientModel {
        id: nm
    }

    remove.onClicked: goBack()
    add.onClicked: nm.add("sat", "Saturated Fat")

    filters.delegate: NutrientFilter {
        width: filters.width
        height: 60

        name.text: model.displayName
    }

    filters.model: nm
}
