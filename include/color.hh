#ifndef _COLOR_H_
#define _COLOR_H_

#include "ext_datatype.hh"

typedef struct _color32
{
    double R;
    double G;
    double B;
    double A;
} color32;

typedef struct _gl_color32
{
    ExtGLdouble R;
    ExtGLdouble G;
    ExtGLdouble B;
    ExtGLdouble A;
} glColor32;

#endif /* _COLOR_H_ */
