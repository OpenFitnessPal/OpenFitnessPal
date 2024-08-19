import QtQuick 2.15

import OFPNative

SearchSettingsPageForm {
    signal goBack

    NutrientModel {
        id: nm
    }

    remove.onClicked: goBack()
    add.onClicked: nm.add("sat", "Saturated Fat", "g")

    filters.height: 60 * filters.count
    filters.model: nm
    filters.delegate: NutrientFilter {
        width: filters.width
        height: 60

        remove.onClicked: {
            settings.rm("avoid_" + model.name)
            nm.removeRow(model.ntID)
        }

        threshold.onValueChanged: {
            model.filter = threshold.value / 100.0
        }
    }

    Component.onCompleted: {
        generics.checked = settings.get("generics")
        results.value = settings.get("results")
        nm.loadFilterData()
    }

    generics.onCheckedChanged: settings.set("generics", generics.checked)
    results.onValueChanged: settings.set("results", results.value)
}
