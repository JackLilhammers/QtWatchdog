#include "mainapp.h"

#include <QCoreApplication>
#include <QtDebug>
#include <QString>

MainApp::MainApp(QStringList arguments, QObject *parent)
    : QObject(parent)
    , args(arguments)
    , watchdog(this)
    , timer(this)

{}

void MainApp::run()
{
    results.push_back(test());
}

bool MainApp::test()
{
    setup();
    t.start();

    bool watchdogStarted = watchdog.start();
    if (!watchdogStarted)
        return false;

    timer.start();

    QTimer::singleShot(N*1000, [this] {
        timer.stop();

        QTimer::singleShot(2000, [this] {
            timer.start();

            QTimer::singleShot(N*1000, [this] {
                timer.stop();

                connect(&watchdog, &Watchdog::timeout,
                        this, &MainApp::finished);
            });
        });
    });

    return true;
}

void MainApp::setup()
{
    connect(&watchdog, &Watchdog::timeout,
            this, &MainApp::onWatchdogTimeout);
    connect(&watchdog, &Watchdog::restarted,
            this, &MainApp::onWatchdogRestarted);

    watchdog.setInterval(1000);

    timer.setInterval(500);
    timer.callOnTimeout(&watchdog, &Watchdog::restart);
}

void MainApp::onWatchdogTimeout()
{
    qDebug() << "timeout after" << t.elapsed()/1000 << "seconds";
}

void MainApp::onWatchdogRestarted()
{
    qDebug() << "restarted after" << t.elapsed()/1000 << "seconds";
}

void MainApp::aboutToQuitApp()
{
    qDebug() << "Results:";

    int counter = 0;

    for (auto result : results)
        qDebug() << "Test " << ++counter << ": "<< result;
}
