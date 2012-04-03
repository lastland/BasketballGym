#include <QtGui/QColor>
#include <QtGui/QColorDialog>
#include "color.hh"

void _color32::getColor()
{
    QColor color = QColorDialog::getColor().toRgb();
    this->R = color.redF();
    this->G = color.greenF();
    this->B = color.blueF();
}

void _gl_color32::getColor()
{
    QColor color = QColorDialog::getColor().toRgb();
    this->R = ExtGLdouble(color.redF());
    this->G = ExtGLdouble(color.greenF());
    this->B = ExtGLdouble(color.blueF());
}
