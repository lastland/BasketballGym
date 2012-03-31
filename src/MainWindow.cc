#include <stdio.h>
#include "scene.hh"
#include "MainWindow.hh"

MainWindow::MainWindow(SceneWidget *scene, QWidget *parent)
    : QMainWindow(parent), Ui::MainWindow()
{
    setupUi(this);
    m_scene = scene;
    scenePartLayout->addWidget(m_scene, 0);

    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), scene, SLOT(updateGL()));
    timer->start(1000.0 / 60.0);

    m_play = false;
    connect(playButton, SIGNAL(clicked()), m_scene, SLOT(toggleState()));
    connect(playButton, SIGNAL(clicked()), this, SLOT(togglePlayButton()));

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
        /* floor color */
        floorLightRBox, &m_scene->m_floorAmbientAndDiffuse.R,
        floorLightGBox, &m_scene->m_floorAmbientAndDiffuse.G,
        floorLightBBox, &m_scene->m_floorAmbientAndDiffuse.B,
        floorLightABox, &m_scene->m_floorAmbientAndDiffuse.A,
        /* basketball position */
        ballPosXBox, &m_scene->m_basketballPos.x,
        ballPosYBox, &m_scene->m_basketballPos.y,
        ballPosZBox, &m_scene->m_basketballPos.z,
        /* basketball velocity */
        ballVelXBox, &m_scene->m_basketballVel.x,
        ballVelYBox, &m_scene->m_basketballVel.y,
        ballVelZBox, &m_scene->m_basketballVel.z,
        /* baksetball radius */
        sphereRadiusBox, &m_scene->m_basketballRadius,
        /* physics reduces */
        airReduceBox, &m_scene->m_airReduce,
        colReduceBox, &m_scene->m_colReduce,
        /* end flag */
        NULL
    };

    QObject *int_buddies[] = {
        sphereSlicesBox, &m_scene->m_basketballSlices,
        sphereStacksBox, &m_scene->m_basketballStacks,
        NULL
    };

    for (int i = 0; double_buddies[i]; i += 2)
    {
        ((QDoubleSpinBox*)double_buddies[i])->setValue(
            ((ExtGLdouble*)double_buddies[i+1])->value());
        connect(double_buddies[i], SIGNAL(valueChanged(double)),
                double_buddies[i+1], SLOT(setValue(double)));
        connect(double_buddies[i+1], SIGNAL(valueChanged(double)),
                double_buddies[i], SLOT(setValue(double)));
    }

    for (int i = 0; int_buddies[i]; i += 2)
    {
        ((QSpinBox*)int_buddies[i])->setValue(
            ((ExtGLuint*)int_buddies[i+1])->value());
        connect(int_buddies[i], SIGNAL(valueChanged(int)),
                int_buddies[i+1], SLOT(setValue(int)));
        connect(int_buddies[i+1], SIGNAL(valueChanged(int)),
                int_buddies[i], SLOT(setValue(int)));
    }
}

void MainWindow::togglePlayButton()
{
    if (m_play)
    {
        m_play = false;
        playButton->setText("Play");
    }
    else
    {
        m_play = true;
        playButton->setText("Pause");
    }
}
