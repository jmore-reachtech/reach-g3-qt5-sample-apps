QT += quick  widgets
CONFIG += c++11

SOURCES += \
        main.cpp

RESOURCES += qml.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /data/app/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

OTHER_FILES += \
    README.md \
    LICENSE
