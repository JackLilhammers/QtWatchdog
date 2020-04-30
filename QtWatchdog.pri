
QTWATCHDOG_LIBNAME = QtWatchdog
win32 {
    CONFIG(release, debug|release) {
        QTWATCHDOG_LIBDIR = $$PWD/build/Release
    } else {
        QTWATCHDOG_LIBDIR = $$PWD/build/Debug
    }
} else {
    QTWATCHDOG_LIBDIR = $$PWD/build
}
INCLUDEPATH += $$PWD
LIBS += -L$$QTWATCHDOG_LIBDIR -l$$QTWATCHDOG_LIBNAME

win32-g++: PRE_TARGETDEPS += $$QTWATCHDOG_LIBDIR/libQtWatchdog.a
else:win32:!win32-g++: PRE_TARGETDEPS += $$QTWATCHDOG_LIBDIR/QtWatchdog.lib
else:unix: PRE_TARGETDEPS += $$QTWATCHDOG_LIBDIR/libQtWatchdog.a
