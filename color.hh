#ifndef _COLOR_H_
#define _COLOR_H_

typedef struct _color32
{
    double R;
    double G;
    double B;
    double A;
} color32;

typedef struct _gl_color32
{
    GLdouble R;
    GLdouble G;
    GLdouble B;
    GLdouble A;
} glColor32;

#endif /* _COLOR_H_ */
