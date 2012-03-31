#ifndef _EXT_DATATYPE_H_
#define _EXT_DATATYPE_H_

#include <QtCore/QObject>
#include <Qt/QtOpenGL>

class ExtGLuint : public QObject
{
    Q_OBJECT
public:

    ExtGLuint(const ExtGLuint &num)
        : QObject(), m_value(num.value()) {}
    
    ExtGLuint(unsigned int value = 0)
        : QObject(), m_value(value) {}
    
    GLuint value(void) const;

    ExtGLuint & operator = (ExtGLuint &num)
    {
        if (m_value != num.value())
        {
            m_value = num.value();
            emit valueChanged(m_value);
        }
        return *this;
    }

    ExtGLuint & operator = (const unsigned int &num)
    {
        if (m_value != num)
        {
            m_value = num;
            emit valueChanged(m_value);
        }
        m_value = num;
        return *this;
    }

    const ExtGLuint operator + (ExtGLuint &num) const
    {
        return ExtGLuint(m_value + num.value());
    }

    const ExtGLuint operator - (ExtGLuint &num) const
    {
        return ExtGLuint(m_value + num);
    }

    GLuint operator ++ ()
    {
        return ++m_value;
    }

    GLuint operator ++ (int)
    {
        return m_value++;
    }

    operator int ()
    {
        return m_value;
    }

signals:
    void valueChanged(int value);

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

    ExtGLdouble(const ExtGLdouble &num)
        : QObject(), m_value(num.value()) {}
    
    ExtGLdouble(double value = 0.0)
        : QObject(), m_value(value) {}
    
    GLdouble value(void) const;
    
    ExtGLdouble & operator = (const ExtGLdouble &num)
    {
        if (m_value != num.value())
        {
            m_value = num.value();
            emit valueChanged(m_value);
        }
        return *this;
    }
    
    ExtGLdouble & operator = (const double &num)
    {
        if (m_value != num)
        {
            m_value = num;
            emit valueChanged(m_value);
        }
        return *this;
    }

    const ExtGLdouble operator + (const ExtGLdouble &num) const
    {
        return ExtGLdouble(m_value + num.value());
    }

    const ExtGLdouble operator - (const ExtGLdouble &num) const
    {
        return ExtGLdouble(m_value - num.value());
    }

    const ExtGLdouble operator * (const ExtGLdouble &num) const
    {
        return ExtGLdouble(m_value * num.value());
    }

    const ExtGLdouble operator * (const double &num) const
    {
        return ExtGLdouble(m_value * num);
    }

    const ExtGLdouble operator / (const ExtGLdouble &num) const
    {
        return ExtGLdouble(m_value / num.value());
    }

    const ExtGLdouble operator / (const double &num) const
    {
        return ExtGLdouble(m_value / num);
    }

    ExtGLdouble operator - () const
    {
        return ExtGLdouble(-m_value);
    }

    bool operator == (const ExtGLdouble &num) const
    {
        return (m_value == num.value());
    }

    bool operator == (const double &num) const
    {
        return (m_value == num);
    }

    bool operator != (const ExtGLdouble &num) const
    {
        return (m_value != num.value());
    }

    bool operator != (const double &num) const
    {
        return (m_value != num);
    }

    bool operator < (const ExtGLdouble &num) const
    {
        return (m_value < num.value());
    }

    bool operator < (const double &num) const
    {
        return (m_value < num);
    }

    bool operator <= (const ExtGLdouble &num) const
    {
        return (m_value <= num.value());
    }

    bool operator <= (const double &num) const
    {
        return (m_value <= num);
    }

    bool operator > (const ExtGLdouble &num) const
    {
        return (m_value > num.value());
    }

    bool operator > (const double &num) const
    {
        return (m_value > num);
    }

    bool operator >= (const ExtGLdouble &num) const
    {
        return (m_value >= num.value());
    }

    bool operator >= (const double &num) const
    {
        return (m_value >= num);
    }

    ExtGLdouble & operator += (const ExtGLdouble &num)
    {
        m_value += num.value();
        if (num.value() != 0)
            emit valueChanged(m_value);
        return *this;
    }

    ExtGLdouble & operator += (const double &num)
    {
        m_value += num;
        if (num != m_value)
            emit valueChanged(m_value);
        return *this;
    }

    ExtGLdouble & operator -= (const ExtGLdouble &num)
    {
        m_value -= num.value();
        if (num.value() != 0)
            emit valueChanged(m_value);
        return *this;
    }

    ExtGLdouble & operator -= (const double &num)
    {
        m_value -= num;
        if (num != 0)
            emit valueChanged(m_value);
        return *this;
    }

    ExtGLdouble & operator *= (const ExtGLdouble &num)
    {
        m_value *= num.value();
        if (num.value() != 1)
            emit valueChanged(m_value);
        return *this;
    }

    ExtGLdouble & operator *= (const double &num)
    {
        m_value *= num;
        if (num != 1)
            emit valueChanged(m_value);
        return *this;
    }

    ExtGLdouble & operator /= (const ExtGLdouble &num)
    {
        m_value /= num.value();
        if (num.value() != 1)
            emit valueChanged(m_value);
        return *this;
    }

    ExtGLdouble & operator /= (const double &num)
    {
        m_value /= num;
        if (num != 1)
            emit valueChanged(m_value);
        
        return *this;
    }

    operator double () const
    {
        return m_value;
    }

signals:
    void valueChanged(double value);

public slots:
    void setValue(double value);
    
private:
    GLdouble m_value;
};

#endif /* _EXT_DATATYPE_H_ */
