#include "ext_datatype.hh"

GLdouble ExtGLdouble::value()
{
    return m_value;
}

void ExtGLdouble::setValue(double value)
{
    m_value = value;
}

GLuint ExtGLuint::value()
{
    return m_value;
}

void ExtGLuint::setValue(unsigned int value)
{
    m_value = value;
}

void ExtGLuint::setValue(int value)
{
    m_value = value;
}
