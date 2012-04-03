#ifndef _COLOR_H_
#define _COLOR_H_

#include <QtCore/QObject>
#include "ext_datatype.hh"

typedef class _color32 : public QObject
{
    Q_OBJECT
public:
    double R;
    double G;
    double B;
    double A;
    
    _color32(double r = 0, double g = 0, double b = 0, double a = 0)
        : R(r), G(g), B(b), A(a) {}

public slots:
    void getColor(void);
    
} color32;

typedef class _gl_color32 : public QObject
{
    Q_OBJECT
public:
    ExtGLdouble R;
    ExtGLdouble G;
    ExtGLdouble B;
    ExtGLdouble A;

    _gl_color32(double r = 0, double g = 0, double b = 0, double a = 0)
        : R(r), G(g), B(b), A(a) {}

public slots:
    void getColor(void);
    
} glColor32;

#endif /* _COLOR_H_ */
