#include <stdio.h>
#include <Qt/QtOpenGL>
#include <GL/glu.h>
#include "qtglut.h"
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

SET_SOME_V3D(GravityA, m_gravity_a);
SET_SOME_V3D(BasketballPos, m_basketballPos);
SET_SOME_V3D(BasketballVel, m_basketballVel);
SET_SOME_V3D(CameraPos, m_cameraPos);
SET_SOME_V3D(CameraCenter, m_cameraCenter);
SET_SOME_V3D(CameraUp, m_cameraUp);
SET_SOME_V3D(LightPos, m_lightPos);

SceneWidget::SceneWidget(QWidget *parent)
    : QGLWidget(parent)
{
    setGravityA(0, -10, 0);
    setBasketball(12.3, 120, 80);
    setBasketballPos(0.0, 100.0, 100.0);
    setBasketballVel(0.0, 0.0, 0.0);
    setCameraPos(400.0, 400.0, -500.0);
    setCameraCenter(250.0, 230.0, 5.0);
    setCameraUp(0.0, 1.0, 0.0);
    setPerspective(60.0, 1.0, 0.1, 9999.0);

    setLightPos(0.0, 0.0, -1.0);
    NUM4_TO_COLOR32(m_lightAmbient, 0.4, 0.4, 0.4, 1.0);
    NUM4_TO_COLOR32(m_lightDiffuse, 1.0, 1.0, 1.0, 1.0);
    NUM4_TO_COLOR32(m_ballAmbientAndDiffuse, 1.0, 0.3, 0.0, 1.0);
    NUM4_TO_COLOR32(m_floorAmbientAndDiffuse, 1.0, 1.0, 1.0, 1.0);

    m_state = STOP;
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

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(m_fovy, m_aspect, m_near, m_far);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(m_cameraPos.x, m_cameraPos.y, m_cameraPos.z,
              m_cameraCenter.x, m_cameraCenter.y, m_cameraCenter.z,
              m_cameraUp.x, m_cameraUp.y, m_cameraUp.z);

    GLfloat light_pos[] = P3D_TO_ARRAY4_WITH_ZERO(m_lightPos);
    GLfloat ambient_light[] = COLOR32_TO_ARRAY4(m_lightAmbient);
    GLfloat diffuse_light[] = COLOR32_TO_ARRAY4(m_lightDiffuse);
    GLfloat ball_ambient_and_diffuse[] = COLOR32_TO_ARRAY4(m_ballAmbientAndDiffuse);
    GLfloat floor_ambient_and_diffuse[] = COLOR32_TO_ARRAY4(m_floorAmbientAndDiffuse);

    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);

    calcBallInNextFrame();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ball_ambient_and_diffuse);
    drawBasketballWhere(m_basketballPos.x, m_basketballPos.y, m_basketballPos.z);
    
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, floor_ambient_and_diffuse);
    drawGym();

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
    glutSolidSphere(m_basketballRadius, m_basketballSlices, m_basketballStacks);
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
    drawFloor();
}

void SceneWidget::calcBallInNextFrame(void)
{
    if (m_state == STOP)
    {
        m_prev = QTime::currentTime();
        m_state = PLAY;
    }
    else
    {
        m_now = QTime::currentTime();
        int msecs = m_prev.msecsTo(m_now);

        m_basketballVel += m_gravity_a * ((double)msecs / 1000.0);
        m_basketballPos += m_basketballVel;
        if (m_basketballPos.y < 0.0)
        {
            m_basketballPos.y = - m_basketballPos.y;
            m_basketballVel = - m_basketballVel;
        }
        
        m_prev = m_now;
    }
}

void SceneWidget::drawFloor(void)
{
    glPushMatrix();
    glTranslatef(0, -1, 700);
    glScalef(1500, 2, 1500);
    glutSolidCube(1);
    glPopMatrix();
}
