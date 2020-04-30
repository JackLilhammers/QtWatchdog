#include "watchdog.h"

#include <stdexcept>

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

void Watchdog::setInterval(int msec)
{
    if (!isValid(msec))
        throw std::invalid_argument("msec < 1\n");

    m_watchdog.setInterval(msec);
}

int Watchdog::interval() const
{
    return m_watchdog.interval();
}

void Watchdog::start(int msec)
{
// Se msec non è accettabile non parte
    setInterval(msec);
    start();
}

void Watchdog::start()
{
    if (!isReady())
        throw std::logic_error("Timeout interval not set!");

    m_watchdog.start(interval());
}

void Watchdog::restart()
{
    if (!m_watchdog.isActive())
        emit restarted();

    start();
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
