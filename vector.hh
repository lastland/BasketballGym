#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "ext_datatype.hh"

typedef struct _vector3d
{
    double x;
    double y;
    double z;
} v3d, p3d, s3d;

typedef struct _gl_vector3d
{
    ExtGLdouble x;
    ExtGLdouble y;
    ExtGLdouble z;
} glP3d, glV3d, glS3d;

#endif /* _VECTOR_H_ */
