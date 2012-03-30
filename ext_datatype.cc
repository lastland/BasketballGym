#include "ext_datatype.hh"

GLdouble ExtGLdouble::value() const
{
    return m_value;
}

void ExtGLdouble::setValue(double value)
{
    if (m_value != value)
    {
        m_value = value;
        emit valueChanged(m_value);
    }
}

GLuint ExtGLuint::value() const
{
    return m_value;
}

void ExtGLuint::setValue(unsigned int value)
{
    if (m_value != value)
    {
        m_value = value;
        emit valueChanged(m_value);
    }
}

void ExtGLuint::setValue(int value)
{
    if (m_value != (unsigned int)value)
    {
        m_value = (unsigned int)value;
        emit valueChanged(m_value);
    }
}
