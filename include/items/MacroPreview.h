#ifndef MACROPREVIEW_H
#define MACROPREVIEW_H

#include "NutrientUnion.h"
#include <QFrame>

namespace Ui {
class MacroPreview;
}

class MacroPreview : public QFrame
{
    Q_OBJECT

public:
    explicit MacroPreview(QWidget *parent = nullptr);
    ~MacroPreview();

    void setNutrients(const NutrientUnion &n);

private:
    Ui::MacroPreview *ui;

    NutrientUnion m_nutrients;

    void mousePressEvent(QMouseEvent *e);
};

#endif // MACROPREVIEW_H
