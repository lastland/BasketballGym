#ifndef _EXT_DATATYPE_H_
#define _EXT_DATATYPE_H_

#include <QtCore/QObject>
#include <Qt/QtOpenGL>

class ExtGLuint : public QObject
{
    Q_OBJECT
public:
    ExtGLuint(unsigned int value = 0)
        : QObject(), m_value(value) {};
    
    GLuint value(void);

    ExtGLuint & operator = (ExtGLuint &num)
    {
        m_value = num.value();
        return *this;
    }

    ExtGLuint & operator = (const unsigned int &num)
    {
        m_value = num;
        return *this;
    }

    operator int ()
    {
        return m_value;
    }

public slots:
    void setValue(unsigned int value);
    void setValue(int value);
    
private:
    GLuint m_value;
};

class ExtGLdouble : public QObject
{
    Q_OBJECT
public:
    ExtGLdouble(double value = 0.0)
        : QObject(), m_value(value) {};
    
    GLdouble value(void);
    
    ExtGLdouble & operator = (ExtGLdouble &num)
    {
        m_value = num.value();
        return *this;
    }
    
    ExtGLdouble & operator = (const double &num)
    {
        m_value = num;
        return *this;
    }

    operator double ()
    {
        return m_value;
    }
                                          
public slots:
    void setValue(double value);
    
private:
    GLdouble m_value;
};

#endif /* _EXT_DATATYPE_H_ */
