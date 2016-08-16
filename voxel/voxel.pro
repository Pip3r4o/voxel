QT += core
QT -= gui

CONFIG += c++11

TARGET = voxel
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

LIBS += -L/usr/local/lib -lSDL2 -lGLEW -lGL -ldl -lpthread
SOURCES += src/main.cpp \
    src/MainGame.cpp \
    src/Sprite.cpp \
    src/GLSLProgram.cpp

HEADERS += \
    src/MainGame.h \
    src/GameState.h \
    src/Sprite.h \
    src/GLSLProgram.h

DISTFILES += \
    style.astylerc \
    shaders/shapes.frag \
    shaders/shapes.vert
