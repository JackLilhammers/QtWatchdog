#include <QCoreApplication>

#include <QTimer>

#include "mainapp.h"

int main(int argc, char *argv[])
{
    QCoreApplication qtCore(argc, argv);
    MainApp app(qtCore.arguments());

    // Connect the signals
    QObject::connect(&app, &MainApp::finished,
                     &qtCore, &QCoreApplication::quit);
    QObject::connect(&qtCore, &QCoreApplication::aboutToQuit,
                     &app, &MainApp::aboutToQuitApp);

    // Enqueue the first event, that launches app.run()
    QTimer::singleShot(0, &app, &MainApp::run);

    // Spin the Qt event loop
    return qtCore.exec();
}
