#include "watchdog.h"

Watchdog::Watchdog(QObject *parent)
    : QObject(parent)
    , m_watchdog(this)
{
    m_watchdog.setSingleShot(true);

    connect(&m_watchdog, &QTimer::timeout,
            this, &Watchdog::timeout);
    clear();
}

bool Watchdog::isReady() const
{
    return isValid(interval());
}

bool Watchdog::isActive() const
{
    return m_watchdog.isActive();
}

bool Watchdog::isValid(int msec) const
{
    return msec > 0;
}

bool Watchdog::setInterval(int msec)
{
    if (!isValid(msec))
        return false;

    m_watchdog.setInterval(msec);
    return true;
}

int Watchdog::interval() const
{
    return m_watchdog.interval();
}

bool Watchdog::start(int msec)
{
// Se msec non è accettabile non parte
    return setInterval(msec) ? start() : false;
}

bool Watchdog::start()
{
    if (!isReady())
        return false;

    m_watchdog.start(interval());
    return true;
}

bool Watchdog::restart()
{
    if (!m_watchdog.isActive())
        emit restarted();

    return start();
}

void Watchdog::stop()
{
    m_watchdog.stop();
}

void Watchdog::clear()
{
    stop();
    m_watchdog.setInterval(0);
}
