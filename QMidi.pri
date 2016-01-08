macx{
    DEFINES += __MACOSX_CORE__=1
    LIBS += -framework CoreMidi
    LIBS += -framework CoreAudio
    LIBS += -framework CoreFoundation
}

linux{
    DEFINES += define __LINUX_ALSA__=1
}
win32{
    DEFINES += __WINDOWS_MM__=1
}
INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/libs/rtmidi


HEADERS += \
    $$PWD/libs/rtmidi/RtMidi.h \
    $$PWD/qmidiin.h \
    $$PWD/qmidiout.h \
    $$PWD/qmidimessage.h \
    $$PWD/qmidimapper.h
SOURCES += \
    $$PWD/libs/rtmidi/RtMidi.cpp \
    $$PWD/qmidiin.cpp \
    $$PWD/qmidiout.cpp \
    $$PWD/qmidimessage.cpp \
    $$PWD/qmidimapper.cpp

DISTFILES += \
    $$PWD/README.md
