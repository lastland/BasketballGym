#ifndef _SCENE_H_
#define _SCENE_H_

#include <QtCore/QTime>
#include <QtOpenGL/QGLWidget>
#include "vector.hh"
#include "color.hh"
#include "sound.hh"

enum SceneState {
    STOP,
    PLAY,
    BACK,
    PAUSE
};

class SceneWidget : public QGLWidget
{
    Q_OBJECT
public:
    SceneWidget(QWidget *parent = NULL);
    void initializeGL(void);
    void resizeGL(int w, int h);
    void paintGL(void);
    void glDraw(void);
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);

    glV3d m_gravity_a;
    void setGravityA(GLdouble x, GLdouble y, GLdouble z);

    ExtGLdouble m_basketballRadius;
    ExtGLuint m_basketballSlices;
    ExtGLuint m_basketballStacks;
    void setBasketball(GLdouble radius, GLuint slices, GLuint stacks);

    glP3d m_basketballPos;
    void setBasketballPos(GLdouble x, GLdouble y, GLdouble z);

    glV3d m_basketballVel;
    void setBasketballVel(GLdouble x, GLdouble y, GLdouble z);

    glP3d m_cameraPos;
    glP3d m_cameraCenter;
    glV3d m_cameraUp;
    void setCameraPos(GLdouble x, GLdouble y, GLdouble z);
    void setCameraCenter(GLdouble x, GLdouble y, GLdouble z);
    void setCameraUp(GLdouble x, GLdouble y, GLdouble z);

    ExtGLdouble m_fovy;
    ExtGLdouble m_aspect;
    ExtGLdouble m_near;
    ExtGLdouble m_far;
    void setPerspective(GLdouble fovy, GLdouble aspect,
                        GLdouble anear, GLdouble afar);

    glP3d m_lightPos;
    glColor32 m_lightAmbient;
    glColor32 m_lightDiffuse;
    glColor32 m_ballAmbientAndDiffuse;
    glColor32 m_floorAmbientAndDiffuse;
    void setLightPos(GLdouble x, GLdouble y, GLdouble z);

    ExtGLdouble m_airReduce;
    ExtGLdouble m_colReduce;

    ExtGLdouble m_playSpeed;
    void setPlaySpeed(double speed);

    glP3d m_boxRangeMin;
    glP3d m_boxRangeMax;
    void setBoxRange(GLdouble minx, GLdouble maxx,
                     GLdouble miny, GLdouble maxy,
                     GLdouble minz, GLdouble maxz);

signals:
    void basketballCol(SoundLevel);
                                                  
public slots:

    void toggleState(void);
    
private:

    /* Used by paintGL. */
    void drawBasketballWhere(GLdouble x, GLdouble y, GLdouble z);
    void drawGym(void);

    /* Used by above methods. */
    void calcBallInNextFrame(void);
    void drawBasketball(void);
    void drawFloor(void);
    glV3d col(double v, double g, double h, double m, double t);

    /* State. */
    SceneState m_state;

    /* Time. */
    QTime m_prev;
    QTime m_now;
};

#endif /* _SCENE_H_ */
