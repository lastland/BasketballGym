#ifndef _SCENE_H_
#define _SCENE_H_

#include <QtCore/QTime>
#include <QtOpenGL/QGLWidget>
#include "vector.hh"
#include "color.hh"

enum SceneState {
    STOP,
    PLAY,
    BACK,
    PAUSE,
};

class SceneWidget : public QGLWidget
{
    Q_OBJECT
public:
    SceneWidget(QWidget *parent = NULL);
    void initializeGL(void);
    void resizeGL(int w, int h);
    void paintGL(void);
    void timerEvent(QTimerEvent *event);

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
                        GLdouble near, GLdouble far);

    glP3d m_lightPos;
    glColor32 m_lightAmbient;
    glColor32 m_lightDiffuse;
    glColor32 m_ballAmbientAndDiffuse;
    glColor32 m_floorAmbientAndDiffuse;
    void setLightPos(GLdouble x, GLdouble y, GLdouble z);

private:

    /* Used by paintGL. */
    void drawBasketballWhere(GLdouble x, GLdouble y, GLdouble z);
    void drawGym(void);

    /* Used by above methods. */
    void calcBallInNextFrame(void);
    void drawBasketball(void);
    void drawFloor(void);

    /* State. */
    SceneState m_state;

    /* Time. */
    QTime m_prev;
    QTime m_now;
};

#endif /* _SCENE_H_ */
