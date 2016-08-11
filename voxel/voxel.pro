QT += core
QT -= gui

CONFIG += c++11

TARGET = voxel
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

LIBS += -L/usr/local/lib -lSDL2 -ldl -lpthread
SOURCES += src/main.cpp \
    src/MainGame.cpp

HEADERS += \
    src/MainGame.h
