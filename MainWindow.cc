#include <stdio.h>
#include "scene.hh"
#include "MainWindow.hh"

MainWindow::MainWindow(SceneWidget *scene, QWidget *parent)
    : QMainWindow(parent), Ui::MainWindow()
{
    setupUi(this);
    m_scene = scene;
    scenePartLayout->addWidget(m_scene);

    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), scene, SLOT(updateGL()));
    timer->start(50);

    QObject *double_buddies[] = {
        /* camera position */
        cameraPosXBox, &m_scene->m_cameraPos.x,
        cameraPosYBox, &m_scene->m_cameraPos.y,
        cameraPosZBox, &m_scene->m_cameraPos.z,
        /* camera center */
        cameraCenterXBox, &m_scene->m_cameraCenter.x,
        cameraCenterYBox, &m_scene->m_cameraCenter.y,
        cameraCenterZBox, &m_scene->m_cameraCenter.z,
        /* which direction is up */
        cameraUpXBox, &m_scene->m_cameraUp.x,
        cameraUpYBox, &m_scene->m_cameraUp.y,
        cameraUpZBox, &m_scene->m_cameraUp.z,
        /* perspective */
        fovyBox, &m_scene->m_fovy,
        aspectBox, &m_scene->m_aspect,
        nearBox, &m_scene->m_near,
        farBox, &m_scene->m_far,
        /* light position */
        lightPosXBox, &m_scene->m_lightPos.x,
        lightPosYBox, &m_scene->m_lightPos.y,
        lightPosZBox, &m_scene->m_lightPos.z,
        /* ambient light color */
        lightAmbientRBox, &m_scene->m_lightAmbient.R,
        lightAmbientGBox, &m_scene->m_lightAmbient.G,
        lightAmbientBBox, &m_scene->m_lightAmbient.B,
        lightAmbientABox, &m_scene->m_lightAmbient.A,
        /* diffuse light color */
        lightDiffuseRBox, &m_scene->m_lightDiffuse.R,
        lightDiffuseGBox, &m_scene->m_lightDiffuse.G,
        lightDiffuseBBox, &m_scene->m_lightDiffuse.B,
        lightDiffuseABox, &m_scene->m_lightDiffuse.A,
        /* basketball color */
        ballLightRBox, &m_scene->m_ballAmbientAndDiffuse.R,
        ballLightGBox, &m_scene->m_ballAmbientAndDiffuse.G,
        ballLightBBox, &m_scene->m_ballAmbientAndDiffuse.B,
        ballLightABox, &m_scene->m_ballAmbientAndDiffuse.A,
        /* basketball position */
        ballPosXBox, &m_scene->m_basketballPos.x,
        ballPosYBox, &m_scene->m_basketballPos.y,
        ballPosZBox, &m_scene->m_basketballPos.z,
        /* baksetball radius */
        sphereRadiusBox, &m_scene->m_basketballRadius,
        /* end flag */
        NULL
    };

    QObject *int_buddies[] = {
        sphereSlicesBox, &m_scene->m_basketballSlices,
        sphereStacksBox, &m_scene->m_basketballStacks,
    };

    for (int i = 0; double_buddies[i]; i += 2)
    {
        ((QDoubleSpinBox*)double_buddies[i])->setValue(
            ((ExtGLdouble*)double_buddies[i+1])->value());
        connect(double_buddies[i], SIGNAL(valueChanged(double)),
                double_buddies[i+1], SLOT(setValue(double)));
    }

    for (int i = 0; int_buddies[i]; i += 2)
    {
        ((QSpinBox*)int_buddies[i])->setValue(
            ((ExtGLuint*)int_buddies[i+1])->value());
        connect(int_buddies[i], SIGNAL(valueChanged(int)),
                int_buddies[i+1], SLOT(setValue(int)));
    }
}
