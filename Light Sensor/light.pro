QT += core quick gui serialbus serialport qml widgets

CONFIG += c++11
INCLUDEPATH += include ../common/include
LIBS += -lasound -lgpiod
TARGET = gpio
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /data/bin
!isEmpty(target.path): INSTALLS += target

SOURCES += \
    ../common/i2c.cpp \
    main.cpp \
    myGlobal.cpp \
    myStyle.cpp \
    ../common/backlight.cpp \
    ../common/beeper.cpp \
    ../common/network.cpp \
    ../common/serialcontroller.cpp \
    ../common/system.cpp \
    ../common/translator.cpp

HEADERS += \
    ../common/include/i2c.h \
    include/myGlobal.h \
    include/myStyle.h \
    ../common/include/backlight.h \
    ../common/include/beeper.h \
    ../common/include/common.h \
    ../common/include/network.h \
    ../common/include/serialcontroller.h \
    ../common/include/sound.h \
    ../common/include/system.h \
    ../common/include/translator.h

DISTFILES += \
    main.qml
