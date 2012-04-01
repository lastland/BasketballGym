#include <cstdio>
#include <cmath>
#include <Qt/QtOpenGL>
#include <GL/glu.h>
#include "qtglut.h"
#include "scene.hh"

const double SIZEX = 1500;
const double MINX = -750;
const double MAXX = MINX + SIZEX;

const double SIZEY = 1500;
const double MINY = 0;
const double MAXY = MINY + SIZEY;

const double SIZEZ = 1500;
const double MINZ = 0;
const double MAXZ = MINZ + SIZEZ;

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

void SceneWidget::setPlaySpeed(double speed)
{
    m_playSpeed = speed;
}

SceneWidget::SceneWidget(QWidget *parent)
    : QGLWidget(parent)
{
    setPlaySpeed(1);
    setBoxRange(MINX, MAXX, MINY, MAXY, MINZ, MAXZ);
    
    setGravityA(0, -980, 0);
    setBasketball(12.3, 120, 80);
    setBasketballPos(0.0, 100.0, 100.0);
    setBasketballVel(0.0, 0.0, 100.0);
    m_airReduce = 0.05;
    m_colReduce = 0.10;
    
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

void SceneWidget::setBoxRange(GLdouble minx, GLdouble maxx,
                              GLdouble miny, GLdouble maxy,
                              GLdouble minz, GLdouble maxz)
{
    m_boxRangeMin.x = minx;
    m_boxRangeMin.y = miny;
    m_boxRangeMin.z = minz;
    m_boxRangeMax.x = maxx;
    m_boxRangeMax.y = maxy;
    m_boxRangeMax.z = maxz;
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

glV3d SceneWidget::col(double v, double g, double h, double m, double t)
{
    double s = h - m;
    if ((v <= 0 && s <= 0) || (v >= 0 && s >= 0))
        return glV3d(0, m, 0);
    double t1;
    if (g != 0)
    {
        t1 = ((v > 0 ? 1 : -1) * sqrt(v * v + (g > 0 ? 2.0 : -2.0) * g * s) - v) / g;
    }
    else
    {
        t1 = - s / v;
    }
    double v1 = v + g * t1;
    double v2 = - (1.0 - m_colReduce) * v1;
    double t2 = t - t1;
    double v3 = v2 + g * t2;
    if (abs(v1) > 400)
        emit basketballCol(HERE);
    else if (abs(v1) > 300)
        emit basketballCol(NEAR);
    else if (abs(v1) > 200)
        emit basketballCol(MIDDLE);
    else if (abs(v1) > 100)
        emit basketballCol(FAR);
    else
        emit basketballCol(VERYFAR);
    return glV3d(v3, m + (v2 + v3) * t2 * 0.5, 0);
}

void SceneWidget::calcBallInNextFrame(void)
{
    if (m_state == PLAY)
    {
        m_now = QTime::currentTime();
        int msecs = m_prev.msecsTo(m_now);

        double t = (double)msecs / 1000.0 * m_playSpeed;
        glV3d a = m_gravity_a;
        glP3d p = m_basketballPos + m_basketballVel * t + a * t * t / 2.0;
        glV3d r;
        glV3d v = m_basketballVel + a * t;
        
        if (p.x < m_basketballRadius + m_boxRangeMin.x)
        {
            r = col(m_basketballVel.x, a.x, m_basketballPos.x, m_boxRangeMin.x + m_basketballRadius, t);
            v.x = r.x;
            p.x = r.y;
        }
        else if (p.x + m_basketballRadius > m_boxRangeMax.x)
        {
            r = col(m_basketballVel.x, a.x, m_basketballPos.x, m_boxRangeMax.x - m_basketballRadius, t);
            v.x = r.x;
            p.x = r.y;
        }
        
        if (p.y < m_basketballRadius + m_boxRangeMin.y)
        {
            r = col(m_basketballVel.y, a.y, m_basketballPos.y, m_boxRangeMin.y + m_basketballRadius, t);
            v.y = r.x;
            p.y = r.y;
        }
        else if (p.y + m_basketballRadius > m_boxRangeMax.y)
        {
            r = col(m_basketballVel.y, a.y, m_basketballPos.y, m_boxRangeMax.y - m_basketballRadius, t);
            v.y = r.x;
            p.y = r.y;
        }
        
        if (p.z < m_basketballRadius + m_boxRangeMin.z)
        {
            r = col(m_basketballVel.z, a.z, m_basketballPos.z, m_boxRangeMin.z + m_basketballRadius, t);
            v.z = r.x;
            p.z = r.y;
        }
        else if (p.z + m_basketballRadius > m_boxRangeMax.z)
        {
            r = col(m_basketballVel.z, a.z, m_basketballPos.z, m_boxRangeMax.z - m_basketballRadius, t);
            v.z = r.x;
            p.z = r.y;
        }

        m_basketballPos = p;
        m_basketballVel = v * (1 - m_airReduce * t);
        
        m_prev = m_now;
    }
}

void SceneWidget::drawFloor(void)
{
    glPushMatrix();
    glTranslatef(MINX + SIZEX / 2, -1, MINZ + SIZEZ / 2);
    glScalef(SIZEX, 2, SIZEZ);
    glutSolidCube(1);
    glPopMatrix();
}

void SceneWidget::toggleState(void)
{
    if (m_state == PLAY)
    {
        m_state = PAUSE;
    }
    else
    {
        m_prev = QTime::currentTime();
        m_state = PLAY;
    }
}
