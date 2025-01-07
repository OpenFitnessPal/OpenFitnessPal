#ifndef SEARCHSETTINGSMANAGER_H
#define SEARCHSETTINGSMANAGER_H

#include <QObject>
#include <QQmlEngine>

#include <QSettings>

class SearchSettingsManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    QSettings m_settings;

public:
    SearchSettingsManager(QObject *parent = nullptr);

    bool preferGenerics() const;
    void setPreferGenerics(bool newPreferGenerics);
    void resetPreferGenerics();

    int results() const;
    void setResults(int newResults);

signals:
    void preferGenericsChanged();
    void resultsChanged();

private:
    Q_PROPERTY(bool preferGenerics READ preferGenerics WRITE setPreferGenerics NOTIFY preferGenericsChanged FINAL)
    Q_PROPERTY(int results READ results WRITE setResults NOTIFY resultsChanged FINAL)
};

#endif // SEARCHSETTINGSMANAGER_H
