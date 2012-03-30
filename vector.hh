#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "ext_datatype.hh"

typedef class _vector3d
{
public:
    double x;
    double y;
    double z;

    _vector3d(const _vector3d &vector3d)
        : x(vector3d.x), y(vector3d.y), z(vector3d.z) {}
    
    _vector3d(double ax = 0, double ay = 0, double az = 0)
        : x(ax), y(ay), z(az) {}

    const _vector3d operator + (const _vector3d &another) const
    {
        return _vector3d(x + another.x, y + another.y, z + another.z);
    }

    const _vector3d operator - (const _vector3d &another) const
    {
        return _vector3d(x - another.x, y - another.y, z - another.z);
    }

    bool operator == (const _vector3d &another) const
    {
        return (x == another.x && y == another.y && z == another.z);
    }

    const _vector3d operator - () const
    {
        return _vector3d(-x, -y, -z);
    }
    
} v3d, p3d, s3d;

typedef class _gl_vector3d
{
public:
    ExtGLdouble x;
    ExtGLdouble y;
    ExtGLdouble z;

    _gl_vector3d(const _gl_vector3d &vector3d)
        : x(vector3d.x.value()), y(vector3d.y.value()), z(vector3d.z.value()) {}

    _gl_vector3d(double ax = 0, double ay = 0, double az = 0)
        : x(ax), y(ay), z(az) {}

    const _gl_vector3d operator + (const _gl_vector3d &another) const
    {
        return _gl_vector3d((double)(x + another.x),
                            (double)(y + another.y),
                            (double)(z + another.z));
    }

    const _gl_vector3d operator - (const _gl_vector3d &another) const
    {
        return _gl_vector3d((double)(x - another.x),
                            (double)(y - another.y),
                            (double)(z - another.z));
    }

    const _gl_vector3d operator * (const double &num) const
    {
        return _gl_vector3d((double)(x * num),
                            (double)(y * num),
                            (double)(z * num));
    }

    const _gl_vector3d operator * (const int &num) const
    {
        return _gl_vector3d((double)(x * (double)num),
                            (double)(y * (double)num),
                            (double)(z * (double)num));
    }

    const _gl_vector3d operator / (const double &num) const
    {
        return _gl_vector3d((double)(x / num),
                            (double)(y / num),
                            (double)(z / num));
    }

    const _gl_vector3d operator / (const int &num) const
    {
        return _gl_vector3d((double)(x / (double)num),
                            (double)(y / (double)num),
                            (double)(z / (double)num));
    }

    _gl_vector3d & operator += (const _gl_vector3d &num)
    {
        x += num.x;
        y += num.y;
        z += num.z;
        return *this;
    }

    _gl_vector3d & operator -= (const _gl_vector3d &num)
    {
        x -= num.x;
        y -= num.y;
        z -= num.z;
        return *this;
    }

    _gl_vector3d & operator *= (const double &num)
    {
        x *= num;
        y *= num;
        z *= num;
        return *this;
    }

    _gl_vector3d & operator /= (const double &num)
    {
        x /= num;
        y /= num;
        z /= num;
        return *this;
    }

    _gl_vector3d & operator *= (const int &num)
    {
        x *= (double)num;
        y *= (double)num;
        z *= (double)num;
        return *this;
    }

    _gl_vector3d & operator /= (const int &num)
    {
        x /= (double)num;
        y /= (double)num;
        z /= (double)num;
        return *this;
    }

    bool operator == (const _gl_vector3d &another) const
    {
        return (x == another.x && y == another.y && z == another.z);
    }

    const _gl_vector3d operator - () const
    {
        return _gl_vector3d((double)-x,
                            (double)-y,
                            (double)-z);
    }
    
} glP3d, glV3d, glS3d;

const _gl_vector3d operator * (double f, _gl_vector3d num);

#endif /* _VECTOR_H_ */
