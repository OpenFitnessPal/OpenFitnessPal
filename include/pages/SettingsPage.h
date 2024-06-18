#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include <QWidget>

namespace Ui {
class SettingsPage;
}

class SettingsPage : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsPage(QWidget *parent = nullptr);
    ~SettingsPage();

public slots:
    void meal1Changed();
    void meal2Changed();
    void meal3Changed();
    void meal4Changed();
    void meal5Changed();
private:
    Ui::SettingsPage *ui;
};

#endif // SETTINGSPAGE_H
