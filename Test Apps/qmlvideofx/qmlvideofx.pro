TEMPLATE = app
TARGET = qmlvideofx

QT += quick multimedia
android: qtHaveModule(androidextras) {
    QT += androidextras
    DEFINES += REQUEST_PERMISSIONS_ON_ANDROID
}

SOURCES += filereader.cpp main.cpp
HEADERS += filereader.h trace.h

RESOURCES += qmlvideofx.qrc

include($$PWD/../snippets/performancemonitor/performancemonitordeclarative.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /data/bin
!isEmpty(target.path): INSTALLS += target

QMAKE_INFO_PLIST = Info.plist

EXAMPLE_FILES += \
    qmlvideofx.png \
    qmlvideofx.svg
