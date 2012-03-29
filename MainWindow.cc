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

    cameraPosXBox->setValue(m_scene->m_cameraPos.x);
    cameraPosYBox->setValue(m_scene->m_cameraPos.y);
    cameraPosZBox->setValue(m_scene->m_cameraPos.z);
    connect(cameraPosXBox, SIGNAL(valueChanged(double)),
            &m_scene->m_cameraPos.x, SLOT(setValue(double)));
    connect(cameraPosYBox, SIGNAL(valueChanged(double)),
            &m_scene->m_cameraPos.y, SLOT(setValue(double)));
    connect(cameraPosZBox, SIGNAL(valueChanged(double)),
            &m_scene->m_cameraPos.z, SLOT(setValue(double)));

    cameraCenterXBox->setValue(m_scene->m_cameraCenter.x);
    cameraCenterYBox->setValue(m_scene->m_cameraCenter.y);
    cameraCenterZBox->setValue(m_scene->m_cameraCenter.z);
    connect(cameraCenterXBox, SIGNAL(valueChanged(double)),
            &m_scene->m_cameraCenter.x, SLOT(setValue(double)));
    connect(cameraCenterYBox, SIGNAL(valueChanged(double)),
            &m_scene->m_cameraCenter.y, SLOT(setValue(double)));
    connect(cameraCenterZBox, SIGNAL(valueChanged(double)),
            &m_scene->m_cameraCenter.z, SLOT(setValue(double)));

    cameraUpXBox->setValue(m_scene->m_cameraUp.x);
    cameraUpYBox->setValue(m_scene->m_cameraUp.y);
    cameraUpZBox->setValue(m_scene->m_cameraUp.z);
    connect(cameraUpXBox, SIGNAL(valueChanged(double)),
            &m_scene->m_cameraUp.x, SLOT(setValue(double)));
    connect(cameraUpYBox, SIGNAL(valueChanged(double)),
            &m_scene->m_cameraUp.y, SLOT(setValue(double)));
    connect(cameraUpZBox, SIGNAL(valueChanged(double)),
            &m_scene->m_cameraUp.z, SLOT(setValue(double)));

    lightAmbientRBox->setValue(m_scene->m_lightAmbient.R);
    lightAmbientGBox->setValue(m_scene->m_lightAmbient.G);
    lightAmbientBBox->setValue(m_scene->m_lightAmbient.B);
    lightAmbientABox->setValue(m_scene->m_lightAmbient.A);
    connect(lightAmbientRBox, SIGNAL(valueChanged(double)),
            &m_scene->m_lightAmbient.R, SLOT(setValue(double)));
    connect(lightAmbientGBox, SIGNAL(valueChanged(double)),
            &m_scene->m_lightAmbient.G, SLOT(setValue(double)));
    connect(lightAmbientBBox, SIGNAL(valueChanged(double)),
            &m_scene->m_lightAmbient.B, SLOT(setValue(double)));
    connect(lightAmbientABox, SIGNAL(valueChanged(double)),
            &m_scene->m_lightAmbient.A, SLOT(setValue(double)));

    lightDiffuseRBox->setValue(m_scene->m_lightDiffuse.R);
    lightDiffuseGBox->setValue(m_scene->m_lightDiffuse.G);
    lightDiffuseBBox->setValue(m_scene->m_lightDiffuse.B);
    lightDiffuseABox->setValue(m_scene->m_lightDiffuse.A);
    connect(lightDiffuseRBox, SIGNAL(valueChanged(double)),
            &m_scene->m_lightDiffuse.R, SLOT(setValue(double)));
    connect(lightDiffuseGBox, SIGNAL(valueChanged(double)),
            &m_scene->m_lightDiffuse.G, SLOT(setValue(double)));
    connect(lightDiffuseBBox, SIGNAL(valueChanged(double)),
            &m_scene->m_lightDiffuse.B, SLOT(setValue(double)));
    connect(lightDiffuseABox, SIGNAL(valueChanged(double)),
            &m_scene->m_lightDiffuse.A, SLOT(setValue(double)));

    ballLightRBox->setValue(m_scene->m_ballAmbientAndDiffuse.R);
    ballLightGBox->setValue(m_scene->m_ballAmbientAndDiffuse.G);
    ballLightBBox->setValue(m_scene->m_ballAmbientAndDiffuse.B);
    ballLightABox->setValue(m_scene->m_ballAmbientAndDiffuse.A);
    connect(ballLightRBox, SIGNAL(valueChanged(double)),
            &m_scene->m_ballAmbientAndDiffuse.R, SLOT(setValue(double)));
    connect(ballLightGBox, SIGNAL(valueChanged(double)),
            &m_scene->m_ballAmbientAndDiffuse.G, SLOT(setValue(double)));
    connect(ballLightBBox, SIGNAL(valueChanged(double)),
            &m_scene->m_ballAmbientAndDiffuse.B, SLOT(setValue(double)));
    connect(ballLightABox, SIGNAL(valueChanged(double)),
            &m_scene->m_ballAmbientAndDiffuse.A, SLOT(setValue(double)));

    sphereRadiusBox->setValue(m_scene->m_basketballRadius);
    sphereSlicesBox->setValue(m_scene->m_basketballSlices);
    sphereStacksBox->setValue(m_scene->m_basketballStacks);
    connect(sphereRadiusBox, SIGNAL(valueChanged(double)),
            &m_scene->m_basketballRadius, SLOT(setValue(double)));
    connect(sphereSlicesBox, SIGNAL(valueChanged(int)),
            &m_scene->m_basketballSlices, SLOT(setValue(int)));
    connect(sphereStacksBox, SIGNAL(valueChanged(int)),
            &m_scene->m_basketballStacks, SLOT(setValue(int)));

    ballPosXBox->setValue(m_scene->m_basketballPos.x);
    ballPosYBox->setValue(m_scene->m_basketballPos.y);
    ballPosZBox->setValue(m_scene->m_basketballPos.z);
    connect(ballPosXBox, SIGNAL(valueChanged(double)),
            &m_scene->m_basketballPos.x, SLOT(setValue(double)));
    connect(ballPosYBox, SIGNAL(valueChanged(double)),
            &m_scene->m_basketballPos.y, SLOT(setValue(double)));
    connect(ballPosZBox, SIGNAL(valueChanged(double)),
            &m_scene->m_basketballPos.z, SLOT(setValue(double)));

    fovyBox->setValue(m_scene->m_fovy);
    aspectBox->setValue(m_scene->m_aspect);
    nearBox->setValue(m_scene->m_near);
    farBox->setValue(m_scene->m_far);
    connect(fovyBox, SIGNAL(valueChanged(double)),
            &m_scene->m_fovy, SLOT(setValue(double)));
    connect(aspectBox, SIGNAL(valueChanged(double)),
            &m_scene->m_aspect, SLOT(setValue(double)));
    connect(nearBox, SIGNAL(valueChanged(double)),
            &m_scene->m_near, SLOT(setValue(double)));
    connect(farBox, SIGNAL(valueChanged(double)),
            &m_scene->m_far, SLOT(setValue(double)));
}
