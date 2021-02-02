QT += core quick gui serialbus serialport qml widgets
LIBS += -lasound
TARGET = mainApp
TEMPLATE = app
INCLUDEPATH += include ../common/include
CONFIG += c++11

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /data/app/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += qml.qrc
DEFINES += QT_DEPRECATED_WARNINGS
DISTFILES +=

SOURCES += \
    main.cpp \
    myGlobal.cpp \
    myStyle.cpp \
    ../common/backlight.cpp \
    ../common/beeper.cpp \
    ../common/gpioController.cpp \
    ../common/network.cpp \
    ../common/serialcontroller.cpp \
    ../common/system.cpp \
    ../common/translator.cpp

HEADERS += \
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

