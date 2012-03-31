#include <Qt/QtGui>
#include "scene.hh"
#include "MainWindow.hh"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    SceneWidget *scene = new SceneWidget;
    MainWindow *mainWindow = new MainWindow(scene);
    mainWindow->show();
    return app.exec();
}
