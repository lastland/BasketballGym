#include <stdio.h>
#include <Qt/QtOpenGL>
#include <GL/glu.h>
#include "scene.hh"

#define COLOR32_TO_ARRAY4(color) \
    {color.R, color.G, color.B, color.A}

#define P3D_TO_ARRAY3(p) \
    {p.x, p.y, p.z}

#define P3D_TO_ARRAY4_WITH_ZERO(p) \
    {p.x, p.y, p.z, 0.0}

#define NUM4_TO_COLOR32(color, r, g, b, a)       \
    color.R = r; \
    color.G = g; \
    color.B = b; \
    color.A = a;

#define SET_SOME_V3D(name, m)                                      \
    void SceneWidget::set##name(GLdouble x, GLdouble y, GLdouble z) \
    { \
    setV3d(&m, x, y, z); \
    }

static inline void setV3d(glV3d *v, GLdouble x, GLdouble y, GLdouble z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

SET_SOME_V3D(BasketballPos, m_basketballPos);
SET_SOME_V3D(CameraPos, m_cameraPos);
SET_SOME_V3D(CameraCenter, m_cameraCenter);
SET_SOME_V3D(CameraUp, m_cameraUp);
SET_SOME_V3D(LightPos, m_lightPos);

SceneWidget::SceneWidget(QWidget *parent)
    : QGLWidget(parent)
{
    setBasketball(1.0, 120, 80);
    setBasketballPos(0.0, 0.0, 5.0);
    setCameraPos(0.0, 0.0, 0.0);
    setCameraCenter(0.0, 0.0, 5.0);
    setCameraUp(0.0, 1.0, 0.0);
    setPerspective(60.0, 1.0, 1.0, 10.0);

    setLightPos(1.0, 1.0, 1.0);
    NUM4_TO_COLOR32(m_diffuseLightColor, 1.0, 1.0, 1.0, 1.0);
    NUM4_TO_COLOR32(m_specularLightColor, 1.0, 1.0, 1.0, 1.0);
    m_matShininess = 30.0;
    NUM4_TO_COLOR32(m_matSpecular, 1.0, 1.0, 1.0, 1.0);
    NUM4_TO_COLOR32(m_modelAmbient, 0.1, 0.1, 0.1, 1.0);
}

void SceneWidget::setPerspective(GLdouble fovy, GLdouble aspect,
                                 GLdouble near, GLdouble far)
{
    m_fovy = fovy;
    m_aspect = aspect;
    m_near = near;
    m_far = far;
}

void SceneWidget::setBasketball(GLdouble radius, GLuint slices, GLuint stacks)
{
    m_basketballRadius = radius;
    m_basketballSlices = slices;
    m_basketballStacks = stacks;
}

void SceneWidget::initializeGL(void)
{
    
    glShadeModel(GL_SMOOTH);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}

void SceneWidget::paintGL(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluPerspective(m_fovy, m_aspect, m_near, m_far);
    gluLookAt(m_cameraPos.x, m_cameraPos.y, m_cameraPos.z,
              m_cameraCenter.x, m_cameraCenter.y, m_cameraCenter.z,
              m_cameraUp.x, m_cameraUp.y, m_cameraUp.z);
    
    GLfloat mat_specular[] = COLOR32_TO_ARRAY4(m_matSpecular);
    GLfloat mat_shininess[] = {m_matShininess};
    GLfloat light_position[] = P3D_TO_ARRAY4_WITH_ZERO(m_lightPos);
    GLfloat diffuse_light[] = COLOR32_TO_ARRAY4(m_diffuseLightColor);
    GLfloat specular_light[] = COLOR32_TO_ARRAY4(m_specularLightColor);
    GLfloat lmodel_ambient[] = COLOR32_TO_ARRAY4(m_modelAmbient);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    
    drawGym();
    drawBasketballWhere(m_basketballPos.x, m_basketballPos.y, m_basketballPos.z);

    swapBuffers();
}

void SceneWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-1.5, 1.5, -1.5 * (GLfloat)h / (GLfloat)w,
                1.5 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
    else
        glOrtho(-1.5 * (GLfloat)w / (GLfloat)h,
                1.5 * (GLfloat)w / (GLfloat)h, -1.5, 1.5, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void SceneWidget::timerEvent(QTimerEvent *event)
{
    updateGL();
}

void SceneWidget::drawBasketball(void)
{
    GLUquadricObj *quadObj = gluNewQuadric();
    gluQuadricDrawStyle(quadObj, GLU_FILL);
    gluQuadricNormals(quadObj, GLU_SMOOTH);
    gluSphere(quadObj, m_basketballRadius, m_basketballSlices, m_basketballStacks);
}

void SceneWidget::drawBasketballWhere(GLdouble x, GLdouble y, GLdouble z)
{
    glPushMatrix();
    glTranslated(x, y, z);
    drawBasketball();
    glPopMatrix();
}

void SceneWidget::drawGym(void)
{
    /* blank now */
}

void SceneWidget::setCameraPosX(double x)
{
    m_cameraPos.x = x;
}

void SceneWidget::setCameraPosY(double y)
{
    m_cameraPos.y = y;
}

void SceneWidget::setCameraPosZ(double z)
{
    m_cameraPos.z = z;
}

void SceneWidget::setCameraCenterX(double x)
{
    m_cameraCenter.x = x;
}

void SceneWidget::setCameraCenterY(double y)
{
    m_cameraCenter.y = y;
}

void SceneWidget::setCameraCenterZ(double z)
{
    m_cameraCenter.z = z;
}

void SceneWidget::setCameraUpX(double x)
{
    m_cameraUp.x = x;
}

void SceneWidget::setCameraUpY(double y)
{
    m_cameraUp.y = y;
}

void SceneWidget::setCameraUpZ(double z)
{
    m_cameraUp.z = z;
}

void SceneWidget::setFovy(double fovy)
{
    m_fovy = fovy;
}

void SceneWidget::setAspect(double aspect)
{
    m_aspect = aspect;
}

void SceneWidget::setNear(double near)
{
    m_near = near;
}

void SceneWidget::setFar(double far)
{
    m_far = far;
}

void SceneWidget::setLightPosX(double x)
{
    m_lightPos.x = x;
}

void SceneWidget::setLightPosY(double y)
{
    m_lightPos.y = y;
}

void SceneWidget::setLightPosZ(double z)
{
    m_lightPos.z = z;
}

void SceneWidget::setBasketballRadius(double radius)
{
    m_basketballRadius = radius;
}

void SceneWidget::setBasketballSlices(int slices)
{
    m_basketballSlices = slices;
}

void SceneWidget::setBasketballStacks(int stacks)
{
    m_basketballStacks = stacks;
}

void SceneWidget::setBasketballPosX(double x)
{
    m_basketballPos.x = x;
}

void SceneWidget::setBasketballPosY(double y)
{
    m_basketballPos.y = y;
}

void SceneWidget::setBasketballPosZ(double z)
{
    m_basketballPos.z = z;
}
