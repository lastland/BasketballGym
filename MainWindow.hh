#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <Qt/QtGui>
#include "scene.hh"
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT
public:
    MainWindow(SceneWidget *scene, QWidget *parent = NULL);

private:
    SceneWidget *m_scene;
};

#endif /* _MAINWINDOW_H_ */
