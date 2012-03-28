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
            m_scene, SLOT(setCameraPosX(double)));
    connect(cameraPosYBox, SIGNAL(valueChanged(double)),
            m_scene, SLOT(setCameraPosY(double)));
    connect(cameraPosZBox, SIGNAL(valueChanged(double)),
            m_scene, SLOT(setCameraPosZ(double)));

    cameraCenterXBox->setValue(m_scene->m_cameraCenter.x);
    cameraCenterYBox->setValue(m_scene->m_cameraCenter.y);
    cameraCenterZBox->setValue(m_scene->m_cameraCenter.z);
    connect(cameraCenterXBox, SIGNAL(valueChanged(double)),
            m_scene, SLOT(setCameraCenterX(double)));
    connect(cameraCenterYBox, SIGNAL(valueChanged(double)),
            m_scene, SLOT(setCameraCenterY(double)));
    connect(cameraCenterZBox, SIGNAL(valueChanged(double)),
            m_scene, SLOT(setCameraCenterZ(double)));

    cameraUpXBox->setValue(m_scene->m_cameraUp.x);
    cameraUpYBox->setValue(m_scene->m_cameraUp.y);
    cameraUpZBox->setValue(m_scene->m_cameraUp.z);
    connect(cameraUpXBox, SIGNAL(valueChanged(double)),
            m_scene, SLOT(setCameraUpX(double)));
    connect(cameraUpYBox, SIGNAL(valueChanged(double)),
            m_scene, SLOT(setCameraUpY(double)));
    connect(cameraUpZBox, SIGNAL(valueChanged(double)),
            m_scene, SLOT(setCameraUpZ(double)));

    lightPosXBox->setValue(m_scene->m_lightPos.x);
    lightPosYBox->setValue(m_scene->m_lightPos.y);
    lightPosZBox->setValue(m_scene->m_lightPos.z);
    connect(lightPosXBox, SIGNAL(valueChanged(double)),
            m_scene, SLOT(setLightPosX(double)));
    connect(lightPosYBox, SIGNAL(valueChanged(double)),
            m_scene, SLOT(setLightPosY(double)));
    connect(lightPosZBox, SIGNAL(valueChanged(double)),
            m_scene, SLOT(setLightPosZ(double)));

    sphereRadiusBox->setValue(m_scene->m_basketballRadius);
    sphereSlicesBox->setValue(m_scene->m_basketballSlices);
    sphereStacksBox->setValue(m_scene->m_basketballStacks);
    connect(sphereRadiusBox, SIGNAL(valueChanged(double)),
            m_scene, SLOT(setBasketballRadius(double)));
    connect(sphereSlicesBox, SIGNAL(valueChanged(int)),
            m_scene, SLOT(setBasketballSlices(int)));
    connect(sphereStacksBox, SIGNAL(valueChanged(int)),
            m_scene, SLOT(setBasketballStacks(int)));

    ballPosXBox->setValue(m_scene->m_basketballPos.x);
    ballPosYBox->setValue(m_scene->m_basketballPos.y);
    ballPosZBox->setValue(m_scene->m_basketballPos.z);
    connect(ballPosXBox, SIGNAL(valueChanged(double)),
            m_scene, SLOT(setBasketballPosX(double)));
    connect(ballPosYBox, SIGNAL(valueChanged(double)),
            m_scene, SLOT(setBasketballPosY(double)));
    connect(ballPosZBox, SIGNAL(valueChanged(double)),
            m_scene, SLOT(setBasketballPosZ(double)));

    fovyBox->setValue(m_scene->m_fovy);
    aspectBox->setValue(m_scene->m_aspect);
    nearBox->setValue(m_scene->m_near);
    farBox->setValue(m_scene->m_far);
    connect(fovyBox, SIGNAL(valueChanged(double)),
            m_scene, SLOT(setFovy(double)));
    connect(aspectBox, SIGNAL(valueChanged(double)),
            m_scene, SLOT(setAspect(double)));
    connect(nearBox, SIGNAL(valueChanged(double)),
            m_scene, SLOT(setNear(double)));
    connect(farBox, SIGNAL(valueChanged(double)),
            m_scene, SLOT(setFar(double)));
}
