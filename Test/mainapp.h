#ifndef MAINAPP_H
#define MAINAPP_H

#include <QObject>
#include <QTime>

#include <vector>

#include "../watchdog.h"

const int N = 3;

class MainApp : public QObject
{
    Q_OBJECT
public:
    explicit MainApp(QStringList arguments, QObject *parent = nullptr);

private:
    bool test();
    void setup();

public slots:
    void run();
    void aboutToQuitApp();

private slots:
    void onWatchdogTimeout();
    void onWatchdogRestarted();

signals:
    void finished();

private:
    QStringList args;
    std::vector<bool> results;
    QTime t;

    Watchdog watchdog;
    QTimer timer;
};

#endif // MAINAPP_H
