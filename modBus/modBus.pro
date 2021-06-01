QT += core quick gui serialbus serialport qml widgets
LIBS += -lasound -lmodbus
TARGET = modBus
TEMPLATE = app
CONFIG += c++11
INCLUDEPATH += include ../common/include

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /data/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += qml.qrc
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    myGlobal.cpp \
    myStyle.cpp \
    modb.cpp \
    writeregistermodel.cpp \
    ../common/backlight.cpp \
    ../common/beeper.cpp \
    ../common/gpioController.cpp \
    ../common/network.cpp \
    ../common/serialcontroller.cpp \
    ../common/system.cpp \
    ../common/translator.cpp

HEADERS += \
    include/modb.h \
    include/writeregistermodel.h \
    include/myGlobal.h \
    include/myStyle.h \
    ../common/include/backlight.h \
    ../common/include/beeper.h \
    ../common/include/common.h \
    ../common/include/gpioController.h \
    ../common/include/i2c-dev.h \
    ../common/include/network.h \
    ../common/include/serialcontroller.h \
    ../common/include/sound.h \
    ../common/include/system.h \
    ../common/include/translator.h

DISTFILES += \
    main.qml
