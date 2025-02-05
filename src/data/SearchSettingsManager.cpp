#include "data/SearchSettingsManager.h"
#include <QtGui/qguiapplication.h>

bool SearchSettingsManager::preferGenerics() const
{
    return m_settings.value("preferGenerics", true).toBool();
}

void SearchSettingsManager::setPreferGenerics(bool newPreferGenerics)
{
    m_settings.setValue("preferGenerics", newPreferGenerics);
    emit preferGenericsChanged();
}

void SearchSettingsManager::resetPreferGenerics()
{
    setPreferGenerics(true);
}

int SearchSettingsManager::results() const
{
    return m_settings.value("results", 10).toInt();
}

void SearchSettingsManager::setResults(int newResults)
{
    m_settings.setValue("results", newResults);
    emit resultsChanged();
}

SearchSettingsManager::SearchSettingsManager(QObject *parent)
    : QObject{parent}
    , m_settings(qApp)
{
}
