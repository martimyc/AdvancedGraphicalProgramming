#-------------------------------------------------
#
# Project created by QtCreator 2019-03-30T20:11:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): DEFINES += ADS_NAMESPACE_ENABLED

windows {
        # MinGW
        *-g++* {
                QMAKE_CXXFLAGS += -std=c++11
        }
        # MSVC
        *-msvc* {
        }
}

TARGET = Engine
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    entitymanager.cpp \
    entity.cpp \
    component.cpp \
    entitymanager.cpp \
    icontitlewidget.cpp \
    dialogs/SectionContentListModel.cpp \
    dialogs/SectionContentListWidget.cpp \
    component.cpp \
    entity.cpp \
    entitymanager.cpp \
    icontitlewidget.cpp \
    main.cpp \
    mainwindow.cpp \
    transformwidget.cpp \
    transform.cpp \
    openglwidget.cpp \
    glinfo.cpp \
    triangle.cpp

HEADERS += \
        mainwindow.h \
    entitymanager.h \
    entity.h \
    component.h \
    entitymanager.h \
    globals.h \
    icontitlewidget.h \
    dialogs/SectionContentListModel.h \
    dialogs/SectionContentListWidget.h \
    component.h \
    entity.h \
    entitymanager.h \
    globals.h \
    icontitlewidget.h \
    mainwindow.h \
    transformwidget.h \
    transform.h \
    openglwidget.h \
    glinfo.h \
    triangle.h

FORMS += \
        mainwindow.ui \
    entitymanager.ui \
    dialogs/SectionContentListWidget.ui \
    transformwidget.ui

RESOURCES += \
    icons.qrc \
    shaders.qrc

# Dependency: AdvancedDockingSystem (shared)
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../AdvancedDockingSystem/release/ -lAdvancedDockingSystem1
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../AdvancedDockingSystem/debug/ -lAdvancedDockingSystem1

INCLUDEPATH += $$PWD/../AdvancedDockingSystem/include
DEPENDPATH += $$PWD/../AdvancedDockingSystem/include

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Shaders/shader1_frag.fsh
