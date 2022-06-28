QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    hamilton.cpp \
    hamiltoncycle.cpp \
    inputmartix.cpp \
    itemline.cpp \
    itempoint.cpp \
    main.cpp \

HEADERS += \
    base.h \
    hamilton.h \
    hamiltoncycle.h \
    inputmartix.h \
    itemline.h \
    itempoint.h \

FORMS += \
    hamiltoncycle.ui \
    inputmartix.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
DISTFILES += \
    Logo.rc \

RC_ICONS = logo.ico

win32-msvc* | win64-msvc* {
    QMAKE_CXXFLAGS *=  /wd"4100"
    contains (QMAKE_CXXFLAGS_WARN_ON, -w34100) : QMAKE_CXXFLAGS_WARN_ON -= -w34100
}
