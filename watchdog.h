#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <QTimer>

class Watchdog final : public QObject
{
    Q_OBJECT
public:
    explicit Watchdog(QObject *parent = nullptr);

public:
    bool isReady() const;
    bool isActive() const;

    void setInterval(int msec);
    int  interval() const;

    void start(int msec);
    void start();
    void restart();
    void stop();
    void clear();

protected:
    bool isValid(int msec) const;

signals:
    void timeout();
    void restarted();

private:
    QTimer m_watchdog;
};

#endif /* WATCHDOG_H */
