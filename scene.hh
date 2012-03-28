#ifndef _SCENE_H_
#define _SCENE_H_

#include <QtOpenGL/QGLWidget>
#include "vector.hh"
#include "color.hh"

class SceneWidget : public QGLWidget
{
    Q_OBJECT
public:
    SceneWidget(QWidget *parent = NULL);
    void initializeGL(void);
    void resizeGL(int w, int h);
    void paintGL(void);
    void timerEvent(QTimerEvent *event);

    GLdouble m_basketballRadius;
    GLuint m_basketballSlices;
    GLuint m_basketballStacks;
    void setBasketball(GLdouble radius, GLuint slices, GLuint stacks);

    glP3d m_basketballPos;
    void setBasketballPos(GLdouble x, GLdouble y, GLdouble z);

    glP3d m_cameraPos;
    glP3d m_cameraCenter;
    glV3d m_cameraUp;
    void setCameraPos(GLdouble x, GLdouble y, GLdouble z);
    void setCameraCenter(GLdouble x, GLdouble y, GLdouble z);
    void setCameraUp(GLdouble x, GLdouble y, GLdouble z);

    GLdouble m_fovy;
    GLdouble m_aspect;
    GLdouble m_near;
    GLdouble m_far;
    void setPerspective(GLdouble fovy, GLdouble aspect,
                        GLdouble near, GLdouble far);

    glP3d m_lightPos;
    glColor32 m_diffuseLightColor;
    glColor32 m_specularLightColor;
    GLdouble m_matShininess;
    glColor32 m_matSpecular;
    glColor32 m_modelAmbient;
    void setLightPos(GLdouble x, GLdouble y, GLdouble z);

public slots:
    void setCameraPosX(double x);
    void setCameraPosY(double y);
    void setCameraPosZ(double z);

    void setCameraCenterX(double x);
    void setCameraCenterY(double y);
    void setCameraCenterZ(double z);

    void setCameraUpX(double x);
    void setCameraUpY(double y);
    void setCameraUpZ(double z);

    void setFovy(double fovy);
    void setAspect(double aspect);
    void setNear(double near);
    void setFar(double far);

    void setLightPosX(double x);
    void setLightPosY(double y);
    void setLightPosZ(double z);

    void setBasketballRadius(double radius);
    void setBasketballSlices(int slices);
    void setBasketballStacks(int slices);

    void setBasketballPosX(double x);
    void setBasketballPosY(double y);
    void setBasketballPosZ(double z);

private:
    void drawBasketball(void);
    void drawBasketballWhere(GLdouble x, GLdouble y, GLdouble z);
    void drawGym(void);
};

#endif /* _SCENE_H_ */
